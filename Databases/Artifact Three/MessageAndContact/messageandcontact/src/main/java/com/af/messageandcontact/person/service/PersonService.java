package com.af.messageandcontact.person.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.af.messageandcontact.person.model.Person;
import com.af.messageandcontact.person.repository.PersonRepository;
import java.util.List;

/**
 * Service calls between DAO and performance business logic.
 * Performs calculations, filters data, general logic, etc.
 */

@Service
public class PersonService {
    
    @Autowired
    PersonRepository personRepository;

    //Create
    public Person createPerson(Person person) {
        return personRepository.save(person);
    }

    //Read Many
    public List<Person> getPersons() {
        return personRepository.findAll();
    }

    //Delete
    public void deletePerson(Long personId) {
        personRepository.deleteById(personId);
    }

    //Update
    public Person updatePerson(Long personId, Person personInfo) {
        Person person = personRepository.findById(personId).get();
        person.setFirst_name(personInfo.getFirst_name());
        person.setLast_name(personInfo.getLast_name());
        person.setGender(personInfo.getGender());
        person.setFull_name(personInfo.getFull_name());

        return personRepository.save(person);
        
    }
}
