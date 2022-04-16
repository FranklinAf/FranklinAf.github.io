package com.af.messageandcontact.person.controller;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.CrossOrigin;

import com.af.messageandcontact.person.model.Person;
import com.af.messageandcontact.person.service.PersonService;

/* Controller called top layer, when api request is made
* Controller handles and processes rest api request
*/
//Specify that this is the controller
@CrossOrigin(origins = "http://localhost:8080")
@RestController
@RequestMapping("/api")
public class PersonController {
    @Autowired
    PersonService personService;

    //Create mapping (POST)
    @RequestMapping(value="/person", method=RequestMethod.POST)
    //@CrossOrigin(origins = "http://localhost:8080")
    public Person createPerson(@RequestBody Person person) {
        return personService.createPerson(person);
    }

    //Read mapping (GET)
    @RequestMapping(value="/person", method=RequestMethod.GET)
    public List<Person> readPersons() {
        return personService.getPersons();
    }

    //Update mapping (PUT)
    @RequestMapping(value="/person/{personId}", method=RequestMethod.PUT)
    public Person readPerson(@PathVariable(value="personId") Long id, 
    @RequestBody Person personInfo) {
        return personService.updatePerson(id, personInfo);
    }

    //Delete mapping (DELETE)
    @RequestMapping(value="/person/{personId}", method=RequestMethod.DELETE)
    public String deletePerson(@PathVariable(value="personId") Long id) {
        try{
            personService.deletePerson(id);
            return String.format("Person %s has been deleted", id);
        }catch(Exception e){
            return e.toString();
        }
        
        
    }
    
    
}
