Given /^I visit the homepage url$/ do
  visit ENV['BASE_URL']
end

Then /^I should see the homepage$/ do
  response_body.should have_selector("title") do |element|
    element.inner_text.should == ENV['TITLE']
  end
end