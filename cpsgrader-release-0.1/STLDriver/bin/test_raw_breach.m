Sys = init_monitor;
P = CreateParamSet(Sys);
Praw = ComputeTraj(Sys, P, Sys.tspan);
Psave(Sys, 'Praw');
formulas= QMITL_ReadFile('current.stl');

Propsave(Sys, formulas{:} );
Breach(Sys);
