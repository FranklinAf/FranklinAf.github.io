package com.af.messageandcontact;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@RestController
public class ExampleController {
    
    @RequestMapping(value =  "/hello", method = RequestMethod.GET )
    public String echo() {
       return "Hello World!";
    }

}
