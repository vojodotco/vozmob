Given /^I am not registered$/ do
end

Given /^I am registered$/ do
  @username.should_not be_empty
end

When /^I submit a Vojo story$/ do
  send_sms 'dev-server@vojo.co', 'This is a registration test ' + Time.now.inspect
  sleep(30)
  puts 'Running cron...'
  visit 'http://dev.vojo.co/cron.php'
  puts 'Done'
  sleep(60)
end

Then /^I should receive a registration confirmation$/ do
  reg_msg = ''
  get_sms
  @sms_messages.each do |msg|
    puts msg
    if msg['message'].include? 'Welcome to'
      reg_msg = msg['message']
    end
  end
  reg_msg.should_not be_empty
  puts reg_msg
  @username = reg_msg.match(/Your username is ([a-zA-Z0-9_\-]+)/m)[1]
  @password = reg_msg.match(/password\s+is\s+([a-zA-Z0-9_\-]+)/m)[1]
  puts @username
  puts @password
end

When /^I send cucumber to the registrar$/ do
  send_sms 'dev-registrar@vojo.co', 'cucumber_user'
  sleep(30)
  visit 'http://dev.vojo.co/cron.php'
  sleep(30)
end

Then /^I should receive a name change confirmation$/ do
  confirmation = ''
  get_sms
  @sms_messages.each do |msg|
    puts msg
    if msg['message'].match(/We changed your .* username/)
      confirmation = msg['message']
    end
  end
  confirmation.should_not be_empty
end