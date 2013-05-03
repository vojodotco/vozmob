Feature: Register Feature
    In order to submit to the site
    As an Anonymous user
    I want to register
    
    Scenario: Register by sending story
        Given I am not registered
        Given a story
        When I sms the story to a group
        Then I should receive an sms registration confirmation
        When I sms "cucumber_user" to the registrar
        Then I should receive an sms name change confirmation
