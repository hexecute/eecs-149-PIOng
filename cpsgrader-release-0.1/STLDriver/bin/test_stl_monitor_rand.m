function test_stl_monitor_rand(stl_test_file, len_trace)

stl_test_file = ['../examples/' stl_test_file];

%trace_file_name = [ sol_path filesep env_name filesep trace_name ];
sys_cmd = ['./stl_monitor -r ' num2str(len_trace) ' ' stl_test_file]

system(sys_cmd);

formulas = QMITL_ReadFile(stl_test_file);
nb_phi = numel(formulas);

% plots in different axes
% figure;
% for ii = 1:nb_phi
%     res = load( [formulas{ii} '.out']);
%     eval([ formulas{ii} '_out = res(:,1:2);']); 
%     subplot(nb_phi,1, ii);
%     plot(res(:,1),res(:,2), 'Color', hsv(i,:));
%     title(formulas{ii}); 
% end

% plots on the same axe
figure;
colors = get(gca, 'ColorOrder');
hold on;
leg = {};
for ii = 1:nb_phi
    res = load( [formulas{ii} '.out']);
    eval([ formulas{ii} '_out = res(:,1:2);']); 
    plot(res(:,1),res(:,2), 'Color', colors(ii,:));
    leg = { leg{:}, formulas{ii}};
end

legend(leg);