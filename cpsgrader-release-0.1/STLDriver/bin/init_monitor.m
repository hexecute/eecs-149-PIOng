function Sys = init_monitor()

name = ['irobot_env'];
signals = {'x', 'y', 'z', 'pitch', 'roll', ...
    'yaw', 'dist', 'angle', 'ax', 'ay', 'az', ...
    'bump_l', 'bump_r', 'drop_l', 'drop_r', ...
    'drop_f', 'cliff_l', 'cliff_fl', 'cliff_fr', ...
    'cliff_r', 'lws', 'rws', 'state'};

params = {'file_no'};
p0 = [1 1];

Sys = CreateExternSystem(name, signals, params, p0, @sim_monitor);


Sys.tspan = 0:.005:100; % default tspan


function fid = dos2unix(fid)
fid = regexprep(fid,'\','/');
