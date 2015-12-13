function [t, X] = sim_monitor(Sys, tspan, p)

%file_no = p(24);
fname = '../../raw_trace.txt'

try
    data = load(fname);
    t = data(:,1)';
    X = data(:,2:end)';
catch me
    warning(me.message);
    t = tspan;
    X = zeros( Sys.DimX, numel(tspan) );
end

t = t - t(1);