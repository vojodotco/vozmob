Given /^I am not registered$/ do
end

Given /^a story$/ do
  @story = 'If you can see this, SMS works! ' + Time.now.inspect  
end

When /^I sms (.+) to (.+)$/ do |message, recipient|
  if /^".+"$/.match(message)
    message = message[1, message.length - 2]
  elsif message == 'the story'
    message = @story
  end
  if /^".+"$/.match(recipient)
    recipient = recipient[1, recipient.length - 2]
  elsif recipient == 'a group'
    recipient = ENV['GROUP_EMAIL']
  elsif recipient == 'the registrar'
    recipient = ENV['REG_EMAIL']
  end
  puts "Sending sms to #{recipient}: #{message}"
  send_sms recipient, message
  sleep(30)
  visit ENV['BASE_URL'] + 'cron.php'
  sleep(120)
end

Then /^I should receive an sms registration confirmation$/ do
  reg_msg = ''
  get_sms
  puts "Received #{@sms_messages.length} message(s)"
  @sms_messages.each do |msg|
    puts msg
    if msg['message'].include? 'Welcome to'
      reg_msg = msg['message']
    end
  end
  reg_msg.should_not be_empty
  puts reg_msg
  @username = reg_msg.match(/username is ([a-zA-Z0-9_\-]+)/m)[1]
  @password = reg_msg.match(/password\s+is\s+([a-zA-Z0-9_\-]+)/m)[1]
  puts @username
  puts @password
end

Then /^I should receive an sms name change confirmation$/ do
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
