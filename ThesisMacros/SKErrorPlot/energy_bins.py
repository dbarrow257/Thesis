e_labels = ['0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-400', '400-1100', '1100-30000',
            '0-30000',
            '0-30000',
            '0-30000',
            '0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-350', '350-800', '800-1250',
            '0-400', '400-1100', '1100-30000',
            '0-30000',
            '0-30000',
            '0-30000',
            '350-800', '800-1250',
            '350-800', '800-1250',
            '350-800', '800-1250',
            '350-800', '800-1250'
]

e_comp_tick = [1, 4, 7, 10,
               13, 15, 16, 17,
               19, 22, 25, 28,
               31, 33, 34, 35,
               36.5, 38.5, 40.5, 42.5]

e_comp_tick = [i+0.5 for i in e_comp_tick]
e_comp_ticklabel = [r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC',
                    r'$\nu_{\mu}$ CCQE', r'$\nu_{\mu}$ CC non-QE', r'$\nu_e$', 'NC',
                    r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC',
                    r'$\nu_{\mu}$ CCQE', r'$\nu_{\mu}$ CC non-QE', r'$\nu_e$', 'NC',
                    r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC']

e_sample_tick = [6, 15, 24, 33, 40]
e_sample_ticklabel = [r"FHC 1R$_e$" , r"FHC 1R$_{\mu}$" ,
                      r"RHC 1R$_e$" , r"RHC 1R$_{\mu}$" ,
                      "FHC 1R$_e$\n1 d.e."]


e_sample_in_tick = [0, 12, 18, 30, 36, 44]
e_sample_in_ticklabel = ["", "", "", "", "", ""]

comp_divs = [3, 6, 9, 15, 16, 17, 21, 24, 27, 33, 34, 35, 38, 40, 42, 44]

sample_divs = [12, 18, 30, 36, 44]

diag_name = "NewDiag_Dan"
matrix_name = "Covariance_Matrix_Erec"
out_string = "Erec"
energy_label = r"Reconstructed $\nu$ energy (MeV)"
