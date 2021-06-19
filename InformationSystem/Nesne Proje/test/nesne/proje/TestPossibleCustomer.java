
package nesne.proje;

import static junit.framework.Assert.assertEquals;
import org.junit.Test;
import org.junit.*;

public class TestPossibleCustomer {
    
    PossibleCustomer customer1=new PossibleCustomer("1111");
    PossibleCustomer customer2=new PossibleCustomer("");
    
    @Test
    public void TestGetCitizenshipNumber(){
        String expect1="1111";
        String expect2="";
        assertEquals(expect1,customer1.getCitizenshipNr()); 
        assertEquals(expect2,customer2.getCitizenshipNr()); 
    }
    
    @Test
    public void TestSetCitizenshipNumber(){
        customer1.setCitizenshipNr("2222");
        customer2.setCitizenshipNr("0000");
        String expect1="2222";
        String expect2="0000";
        assertEquals(expect1,customer1.getCitizenshipNr()); 
        assertEquals(expect2,customer2.getCitizenshipNr()); 
    }
    
    @Test
    public void TestSetName(){
        customer1.setName("Abdo");
        customer2.setName("Abdullah");
        String expect1="Abdo";
        String expect2="Abdullah";
        assertEquals(expect1,customer1.getName());
        assertEquals(expect2,customer2.getName());
    }
    
    @Test
    public void TestSetTel(){
        customer1.setTel("777");
        customer2.setTel("9999");
        String expect1="777";
        String expect2="9999";
        assertEquals(expect1,customer1.getTel());
        assertEquals(expect2,customer2.getTel());
    }
    
    @Test
    public void TestSetMail(){
        customer1.setMail("customer@ex.com");
        customer2.setMail("qq@ex.com");
        String expect1="customer@ex.com";
        String expect2="qq@ex.com";
        assertEquals(expect1,customer1.getMail());
        assertEquals(expect2,customer2.getMail());
    }

    

    
    
    
    
}
