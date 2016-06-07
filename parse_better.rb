filename = ARGV[0]
lines = IO.readlines(filename)

idx = (1..lines.size).detect {|i| /^General/i =~ lines[i]}
# puts idx

/\b(?<ntask>\d+)\b/ =~ lines[idx += 1]
/\b(?<nres>\d+)\b/ =~ lines[idx += 1]
/\b(?<nskill>\d+)\b/ =~ lines[idx += 2]

puts ntask, nres, nskill

idx += 3
resources = []
nres.to_i.times do
  res = Hash.new
  res[:skills] = Hash.new
  /^(?<r_id>\d+)\s+(?<sal>[\d\.]+)\b/ =~ lines[idx]
  res[:id] = r_id
  res[:salary] = sal
  while i = /Q(?<skill_id>\d+)\:\s*(?<level>\d+)/ =~ lines[idx] do
    res[:skills][skill_id] = level
    lines[idx][i] = '!'
  end
  resources << res
  idx += 1
end

puts resources

idx += 2
tasks_hash = Hash.new
# Task = Struct.new(:dur, )
ntask.to_i.times do
  task = Hash.new
  /(?<task_id>\d+)\s+(?<duration>\d+)\s+Q(?<skill_id>\d+)\:\s+(?<skill_req>\d+)/ =~ lines[idx]
  i = Regexp.last_match.offset(0)[1]
  task[:id] = task_id
  task[:dur] = duration
  task[:skill_id] = skill_id
  task[:req] = skill_req
  tasks_hash[task_id] = task

  task[:dep] = []
  
  while /\b(?<dep>\d+)\b/ =~ lines[idx][i..-1] do
    task[:dep] << dep
    i += Regexp.last_match.offset(0)[1]
  end

  idx += 1
end

# puts tasks_hash

tasks = []
# [task_id]
keys = tasks_hash.keys
# inv_keys {task_id => idx}
inv_keys = Hash.new
keys.each_with_index {|k, i| inv_keys[k] = i}

keys.each do |k|
  task = tasks_hash[k]
  task[:dep].map! {|task_id| inv_keys[task_id]}
  tasks << task
end

tasks.each do |task|
  s_id = task[:skill_id]
  req = task[:req]
  task[:resources] = []
  resources.each_with_index do |res, i|
    task[:resources] << i if res[:skills][s_id] && res[:skills][s_id] >= req
  end
  # task[:resources] = resources.select {|r| r[s_id] >= req}.map {|r| r[:res_id]}
end

puts tasks


File.open(filename.gsub(/\.def$/, '.ndef'), 'w') do |out|
  out << "#{ntask} #{nres}\n" # 
  resources.each do |res|
    # out << "#{res[:id]} #{res[:skills].size}"
    # res[:skills].each {|k, v| out << " #{k} #{v}"}
    # out << "\n"
    out << "#{res[:id]} #{res[:salary]}\n"
  end
  tasks.each do |task|
    out << "#{task[:id]} #{task[:dur]} #{task[:dep].size}" #  #{task[:skill_id]} #{task[:req]}
    task[:dep].each {|t_id| out << " #{t_id}"}
    out << " #{task[:resources].size}"
    task[:resources].each {|r_id| out << " #{r_id}"}
    out << "\n"
  end
end
