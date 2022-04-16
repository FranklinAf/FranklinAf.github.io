package com.af.messageandcontact.person.model;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

//Model, what does the table structure look like?
/** Model contains java objects that are mapped to database
 * tables. DAO will fetch the data based on this model
 * will return information to service layer.
 */

@Entity
@Table(name = "person")
public class Person {
    
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) // let database column identity determine primary key strategy
    @Column(name="person_id")
    private Long id;

    @Column(name="first_name", length = 255)
    private String first_name;

    @Column(name="last_name", length = 255)
    private String last_name;

    @Column(name="gender")
    private int gender;

    @Column(name="full_name", length = 510)
    private String full_name;

    //setup constructor
    public Person() {
    }

    public Person(String fname,String lname, int gender, String full) {
        super();
        this.first_name = fname;
        this.last_name = lname;
        this.gender = gender;
        this.full_name = full;
      }

    //Getters and setters
    /**
     * @return Long return the id
     */
    public Long getId() {
        return id;
    }

    /**
     * @param id the id to set
     */
    public void setId(Long id) {
        this.id = id;
    }

    /**
     * @return String return the first_name
     */
    public String getFirst_name() {
        return first_name;
    }

    /**
     * @param first_name the first_name to set
     */
    public void setFirst_name(String first_name) {
        this.first_name = first_name;
    }

    /**
     * @return String return the last_name
     */
    public String getLast_name() {
        return last_name;
    }

    /**
     * @param last_name the last_name to set
     */
    public void setLast_name(String last_name) {
        this.last_name = last_name;
    }

    /**
     * @return int return the gender
     */
    public int getGender() {
        return gender;
    }

    /**
     * @param gender the gender to set
     */
    public void setGender(int gender) {
        this.gender = gender;
    }

    /**
     * @return String return the full_name
     */
    public String getFull_name() {
        return full_name;
    }

    /**
     * @param full_name the full_name to set
     */
    public void setFull_name(String full_name) {
        this.full_name = full_name;
    }

}
