# not a function file.

instanceNum = 20
featureNum = 8
groupNum = 4

#### create dataset file ####
a = rand(instanceNum, featureNum - 1);
b = (a > 0.6667) * 2 + (a < 0.6667 & a > 0.3334);
c = round(rand(instanceNum, 1));
# the feature matrix
dataset = [b c]
# write to dataset file
dlmwrite('dataset-1.txt', [instanceNum featureNum], ' ', 'newline',
'pc');
dlmwrite('dataset-1.txt', dataset, ' ', 'append', 'on', 'newline', 'pc');

#### create partition file ####
partition = {}
fid = fopen('partition-2.txt', 'w');
e = randperm(instanceNum)
divider = sort(ceil((instanceNum - 1)* rand(1,groupNum - 1)))
boundary = unique([0 divider instanceNum])
for i = 1 : numel(boundary) - 1
    fprintf(fid, '%c ', floor(rand*26+65));
    fprintf(fid, ' %s\n', int2str(e(boundary(i) + 1 : boundary(i + 1))));
    partition{i} = e(boundary(i) + 1 : boundary(i + 1));
end
fclose(fid);
