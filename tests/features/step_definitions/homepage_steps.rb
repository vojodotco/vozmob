Given /^I have opened the homepage$/ do
  visit ENV['BASE_URL']
end

Then /^the title should be correct$/ do
  response_body.should have_selector("title") do |element|
    element.inner_text.should == ENV['TITLE']
  end
end