require 'net/http'
require 'uri'
require 'json'

module SmsHelpers
  
  def send_sms(to, body)
    params = {:to => '6245', :body => "#{to} #{body}"}
    Net::HTTP.post_form(URI.parse(ENV['GATEWAY'] + 'send.php'), params)
  end
  
  def get_sms
    postData = Net::HTTP.post_form(URI.parse(ENV['GATEWAY'] + 'messages.php'), {})
    @sms_messages = JSON.parse(postData.body)
  end
  
end
World(SmsHelpers)
