compile_obj__=1;
compile_mex__=1;
compile_simulink__=1;

src_cpp = {'stl_parser.cpp' ... 
          'stl_scanner.cpp '....
          'stl_driver.cpp '....
          'tools.cpp '....
          'stl_atom.cpp '....
          'transducer.cpp '....
          'interval_transducer.cpp '....
          'interval.cpp '....
          'robustness.cpp '....
          'signal.cpp '....
          'signal_expr.cpp '....
          };

%% Obj files

cxxflags = '-DYYDEBUG=1 CXXFLAGS=''$CXXFLAGS -Wno-write-strings -std=c++11 -std=gnu++0x''';
includes = '-I../include/ -I./ -I../';

if ispc
    obj_ext = 'obj';
else
    obj_ext = 'o';
end

objs= '';
for i_src = 1:numel(src_cpp)
    obj = regexprep(src_cpp(i_src),'cpp', obj_ext);
    objs = [objs ' ' obj{1}];
end

if (compile_obj__)
for i_src = 1:numel(src_cpp)
    cmd= sprintf('mex -c %s %s %s', cxxflags, includes, src_cpp{i_src});
    fprintf(cmd);
    fprintf('\n');
    eval(cmd);
end
end

if (compile_mex__)
    cmd_exe = sprintf('mex  %s %s %s %s', cxxflags, includes, 'stl_eval_mex.cpp', objs)
    eval(cmd_exe)
end

if (compile_simulink__)
cmd_simulink = sprintf('mex  %s %s %s %s', cxxflags, includes, 'onlineMonitorWrapper.cpp', objs)
eval(cmd_simulink)
end