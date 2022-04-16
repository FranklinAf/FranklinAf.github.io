package com.af.messageandcontact.person.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.af.messageandcontact.person.model.Person;

/**
 * Creates abstraction between DAO and other layers.
 * DAO connects and accesses, this provides that accessibility
 * to that layer
 */

public interface PersonRepository extends JpaRepository<Person, Long> {
    
}
