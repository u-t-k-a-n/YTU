package nesne.proje;

import java.util.Date;
import static junit.framework.Assert.assertEquals;
import org.junit.Test;
import org.junit.*;

public class TestExistingCustomer{
    
    
    ServiceProvider gsm_provider1=new GSMProvider("GSM Provider-1");
    ServiceProvider cable_provider1=new CableProvider("Cable Provider-1");
    
    SubscriptionPlan sub_plan1=new SubscriptionPlan("Subscription Plan-1");
    SubscriptionPlan sub_plan2=new SubscriptionPlan("Subscription Plan-2",gsm_provider1);
    SubscriptionPlan sub_plan3=new SubscriptionPlan("Subscription Plan-3");
    SubscriptionPlan sub_plan4=new SubscriptionPlan("Subscription Plan-4",cable_provider1);
    Date date1=new Date(2000,1,1);
    
    Subscription sub1=new Subscription(date1,sub_plan1);
    Subscription sub2=new Subscription(date1,sub_plan2);
    Subscription sub3=new Subscription(date1,sub_plan3);
    Subscription sub4=new Subscription(date1,sub_plan4);
    
    ExistingCustomer customer1=new ExistingCustomer("111");
    ExistingCustomer customer2=new ExistingCustomer("222",sub1);
    ExistingCustomer customer3=new ExistingCustomer("333",sub2);
    ExistingCustomer customer4=new ExistingCustomer("444",sub3);
    ExistingCustomer customer5=new ExistingCustomer("555",sub4);
    
    @Test
    public void TestGetCitizenshipNumber(){
        String expect1="111";
        String expect2="222";
        String expect3="333";
        String expect4="444";
        String expect5="555";
        assertEquals(expect1,customer1.getCitizenshipNr());
        assertEquals(expect2,customer2.getCitizenshipNr());
        assertEquals(expect3,customer3.getCitizenshipNr());
        assertEquals(expect4,customer4.getCitizenshipNr());
        assertEquals(expect5,customer5.getCitizenshipNr());
    }
    
    @Test
    public void TestSetCitizenshipNumber(){
        customer1.setCitizenshipNr("1111");
        customer2.setCitizenshipNr("2222");
        customer3.setCitizenshipNr("3333");
        customer4.setCitizenshipNr("4444");
        customer5.setCitizenshipNr("5555");
        String expect1="1111";
        String expect2="2222";
        String expect3="3333";
        String expect4="4444";
        String expect5="5555";
        assertEquals(expect1,customer1.getCitizenshipNr());
        assertEquals(expect2,customer2.getCitizenshipNr());
        assertEquals(expect3,customer3.getCitizenshipNr());
        assertEquals(expect4,customer4.getCitizenshipNr());
        assertEquals(expect5,customer5.getCitizenshipNr());
    }
    
    @Test
    public void TestSetName(){
        customer1.setName("Customer-1");
        customer2.setName("Customer-2");
        customer3.setName("Customer-3");
        customer4.setName("Customer-4");
        customer5.setName("Customer-5");
        String expect1="Customer-1";
        String expect2="Customer-2";
        String expect3="Customer-3";
        String expect4="Customer-4";
        String expect5="Customer-5";
        assertEquals(expect1,customer1.getName()); 
        assertEquals(expect2,customer2.getName()); 
        assertEquals(expect3,customer3.getName()); 
        assertEquals(expect4,customer4.getName()); 
        assertEquals(expect5,customer5.getName()); 
    }
    
    @Test
    public void TestSetTel(){
        customer1.setTel("1");
        customer2.setTel("2");
        customer3.setTel("3");
        customer4.setTel("4");
        customer5.setTel("5");
        String expect1="1";
        String expect2="2";
        String expect3="3";
        String expect4="4";
        String expect5="5";
        assertEquals(expect1,customer1.getTel());
        assertEquals(expect2,customer2.getTel());
        assertEquals(expect3,customer3.getTel());
        assertEquals(expect4,customer4.getTel());
        assertEquals(expect5,customer5.getTel());
    }
    
    @Test
    public void TestSetMail(){
        customer1.setMail("customer1@ex.com");
        customer2.setMail("customer2@ex.com");
        customer3.setMail("customer3@ex.com");
        customer4.setMail("customer4@ex.com");
        customer5.setMail("customer5@ex.com");
        String expect1="customer1@ex.com";
        String expect2="customer2@ex.com";
        String expect3="customer3@ex.com";
        String expect4="customer4@ex.com";
        String expect5="customer5@ex.com";
        assertEquals(expect1,customer1.getMail());
        assertEquals(expect2,customer2.getMail());
        assertEquals(expect3,customer3.getMail());
        assertEquals(expect4,customer4.getMail());
        assertEquals(expect5,customer5.getMail());
    }
    
    @Test
    public void TestGetSubscription(){
        Subscription expect1=sub1;
        Subscription expect2=sub2;
        Subscription expect3=sub3;
        Subscription expect4=sub4;
        assertEquals(null,customer1.getSubscription());
        assertEquals(expect1,customer2.getSubscription());
        assertEquals(expect2,customer3.getSubscription());
        assertEquals(expect3,customer4.getSubscription());
        assertEquals(expect4,customer5.getSubscription());      
    }
    
    @Test
    public void TestSetSubscription(){
        customer1.setSubscription(sub1);
        customer2.setSubscription(sub2);
        customer3.setSubscription(sub3);
        customer4.setSubscription(sub4);
        customer5.setSubscription(sub1);
        Subscription expect1=sub1;
        Subscription expect2=sub2;
        Subscription expect3=sub3;
        Subscription expect4=sub4;
        assertEquals(expect1,customer1.getSubscription());
        assertEquals(expect2,customer2.getSubscription());
        assertEquals(expect3,customer3.getSubscription());
        assertEquals(expect4,customer4.getSubscription());
        assertEquals(expect1,customer5.getSubscription());      
    }
    
    
    
}