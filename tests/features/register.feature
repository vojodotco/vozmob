Feature: Register Feature
    In order to submit to the site
    As an Anonymous user
    I want to register
    
    Scenario: Register by sending story
        Given I am not registered
        When I submit a Vojo story
        Then I should receive a registration confirmation
        When I send cucumber to the registrar
        Then I should receive a name change confirmation
        
