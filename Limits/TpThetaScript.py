execfile("common.py")

def get_model():
    model = build_model_from_rootfile('Theta.root', include_mc_uncertainties = True)

    # define what the signal processes are. All other processes are assumed to make up the  'background-only' model.
    #model.set_signal_processes('th*')
    #model.set_signal_processes('tz*')
    model.set_signal_processes('*750')
    
    # add a minimum MC stat. uncertainty corresponding to +-1 MC event in each bins (esp. empty bins)
    model.fill_histogram_zerobins(1.0)
    
    # Specifying all uncertainties. Internally, this adds a factor exp(lambda * p)
    # where p is the parameter specified as first argument and lambda is the constant
    # in the second argument:

    model.add_lognormal_uncertainty('ewk_rate_BW', 0.1,'ewk','mu_BW')
    model.add_lognormal_uncertainty('ewk_rate_BW', 0.1,'ewk','mu_BWL')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','mu_TZ')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','mu_TH')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','mu_TX')
    model.add_lognormal_uncertainty('ttbar_rate', 0.05, 'ttbar')
    model.add_lognormal_uncertainty('ttbar_rate', 0.1, 'stop')
    model.add_lognormal_uncertainty('qcd_rate', 0.3, 'qcd', 'ele_TZ')
    model.add_lognormal_uncertainty('qcd_rate', 0.3, 'qcd', 'ele_TH')
    model.add_lognormal_uncertainty('qcd_rate', 0.3, 'qcd', 'ele_TX')
    model.add_lognormal_uncertainty('qcd_rate', 0.3, 'qcd', 'ele_BW')
    model.add_lognormal_uncertainty('qcd_rate', 0.3, 'qcd', 'ele_BWL')
    model.add_lognormal_uncertainty('ttbar_rate_TZ', 0.05, 'ttbar', 'mu_TZ')
    model.add_lognormal_uncertainty('ttbar_rate_TH', 0.05, 'ttbar', 'mu_TH')
    model.add_lognormal_uncertainty('ttbar_rate_TX', 0.05, 'ttbar', 'mu_TX')
    model.add_lognormal_uncertainty('ttbar_rate_BW', 0.05, 'ttbar', 'mu_BW')
    model.add_lognormal_uncertainty('ttbar_rate_BWL', 0.05, 'ttbar', 'mu_BWL')

    model.add_lognormal_uncertainty('ewk_rate_BW', 0.1,'ewk','ele_BW')
    model.add_lognormal_uncertainty('ewk_rate_BW', 0.1,'ewk','ele_BWL')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','ele_TZ')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','ele_TH')
    model.add_lognormal_uncertainty('ewk_rate_TX', 0.1,'ewk','ele_TX')
    model.add_lognormal_uncertainty('ttbar_rate_TZ', 0.05, 'ttbar', 'ele_TZ')
    model.add_lognormal_uncertainty('ttbar_rate_TH', 0.05, 'ttbar', 'ele_TH')
    model.add_lognormal_uncertainty('ttbar_rate_TX', 0.05, 'ttbar', 'ele_TX')
    model.add_lognormal_uncertainty('ttbar_rate_BW', 0.05, 'ttbar', 'ele_BW')
    model.add_lognormal_uncertainty('ttbar_rate_BWL', 0.05, 'ttbar', 'ele_BWL')
                                                    

    model.add_lognormal_uncertainty('topPt', 0.1, 'ttbar')

 
    # the qcd is derived from data, so do not apply a lumi uncertainty on that:
    for p in model.processes:
        model.add_lognormal_uncertainty('lumi', 0.045, p)
        model.add_lognormal_uncertainty('jes', 0.07, p)
        model.add_lognormal_uncertainty('tau21', 0.15, p, 'ele_TZ')
        model.add_lognormal_uncertainty('tau21', 0.15, p, 'ele_TH')
        model.add_lognormal_uncertainty('tau21', 0.15, p, 'ele_TX')

        if p == 'qcd': continue

        model.add_lognormal_uncertainty('tau21', 0.15, p, 'mu_TZ')
        model.add_lognormal_uncertainty('tau21', 0.15, p, 'mu_TH')
        model.add_lognormal_uncertainty('tau21', 0.15, p, 'mu_TX')
                        
    return model


model = get_model()


# model_summary(model)
# report.write_html('htmlout')



# maximum likelihood fit on data for each signal mass in turn. (See common.py for the implementation of mle_print)
#mle_print(model, 'data', 1, signal_process_groups = {'zp1000': ['zp1000'] })

# maximum likelihood fit on data without signal (background-only).
#mle_print(model, 'data', 1, signal_process_groups = {'bkgonly': [] })


result = zvalue_approx(model, 'data', 1)
for signal in result:
    print signal, result[signal]['Z']


# test the Z-value distribution for toys:
#result = zvalue_approx(model, 'toys:1.0', 1000)
#for signal in result:
#    plot_histogram(result[signal]['Z'], 'histo-toys-Z-%s.pdf' % signal, logy = True, ymin = 0.5)


expected, observed = asymptotic_cls_limits(model)
print expected, observed
report.write_html('htmlout')



#options = Options()
#options.set('main', 'n_threads', '10')
#expected, observed = bayesian_limits(model, options = options)
#print expected, observed
#report.write_html('htmlout')

