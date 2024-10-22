% Load the .fig file
fig = openfig('untitled.fig', 'invisible');  % Load the figure invisibly
axesHandle = get(fig, 'CurrentAxes');           % Get the axes handle
lines = findobj(axesHandle, 'Type', 'line');    % Find all line objects (data series)

% Initialize cell arrays to hold data for multiple plots
xData = cell(1, length(lines));  % X-axis data (time or other independent variable)
yData = cell(1, length(lines));  % Y-axis data (signal or dependent variable)

% Loop through each line to extract the X and Y data
for i = 1:length(lines)
    xData{i} = get(lines(i), 'XData');  % XData for plot i
    yData{i} = get(lines(i), 'YData');  % YData for plot i
end

% Close the figure after extracting data
close(fig);
