e_labels = ['0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-400', '400-1100', '1100-30000',
            '0-30000',
            '0-30000',
            '0-30000',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-400', '400-1100', '1100-30000',
            '0-30000',
            '0-30000',
            '0-30000',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-300', '300-700', r'$\geq$ 700',
            '0-800', '800-2000', '2000-30000',
            '0-800', '800-2000', '2000-30000',
            '0-800', '800-2000', '2000-30000',
            '0-1500', '1500-2500', '2500-30000',
            '0-30000']

e_comp_tick = [1, 4, 7, 10,
               13, 15, 16, 17,
               19, 22, 25, 28,
               31, 33, 34, 35,
               37, 40, 43, 46,
               49, 52, 55, 58, 60]

e_comp_tick = [i+0.5 for i in e_comp_tick]
e_comp_ticklabel = [r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC',
                    r'$\nu_{\mu}$ CCQE', r'$\nu_{\mu}$ CC non-QE', r'$\nu_e$', 'NC',
                    r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC',
                    r'$\nu_{\mu}$ CCQE', r'$\nu_{\mu}$ CC non-QE', r'$\nu_e$', 'NC',
                    r'$\nu_{\mu} \rightarrow \nu_{e}$', r'$\nu_{\mu}$', r'$\nu_e \rightarrow \nu_e$', 'NC',
                    r'$\nu_{\mu}$CC1$\pi^+$', r'$\nu_{\mu}$CCQE', r'$\nu_{\mu}$CC other', 'NC', r'$\nu_e$CC']

e_sample_tick = [6, 15, 24, 33, 42, 54]
e_sample_ticklabel = [r"FHC 1R$_e$" , r"FHC 1R$_{\mu}$" ,
                      r"RHC 1R$_e$" , r"RHC 1R$_{\mu}$" ,
                      "FHC 1R$_e$\n1 d.e.", r"FHC MR$_{\mu}$"]


e_sample_in_tick = [0, 12, 18, 30, 36, 48, 61]
e_sample_in_ticklabel = ["", "", "", "", "", "", ""]

comp_divs = [3, 6, 9, 15, 16, 17, 21, 24, 27, 33, 34, 35, 39, 42, 45, 48, 51, 54, 57, 60]

sample_divs = [12, 18, 30, 36, 48]

diag_name = "diagonal_P"
matrix_name = "Covariance_Matrix_P"
out_string = "momentum"
energy_label = r"Reconstructed $e$ momentum (MeV/c), reconstructed $\nu_\mu$ energy (MeV)"
