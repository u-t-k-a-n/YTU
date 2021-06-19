
package nesne.proje;

import java.util.Date;
import static junit.framework.Assert.assertEquals;
import org.junit.Test;
import org.junit.*;

public class TestSubscription {
    ServiceProvider gsm_provider1=new GSMProvider("GSM Provider-1");
    ServiceProvider cable_provider1=new CableProvider("Cable Provider-1");
    
    SubscriptionPlan sub_plan1=new SubscriptionPlan("Subscription Plan-1");
    SubscriptionPlan sub_plan2=new SubscriptionPlan("Subscription Plan-2",gsm_provider1);
    SubscriptionPlan sub_plan3=new SubscriptionPlan("Subscription Plan-3");
    SubscriptionPlan sub_plan4=new SubscriptionPlan("Subscription Plan-4",cable_provider1);
    
    Date date1=new Date(2000,1,1);
    Date date2=new Date(2000,2,1);
    Date date3=new Date(2000,3,1);
    Date date4=new Date(2000,4,1);
    
    Subscription sub1=new Subscription(date1,sub_plan1);
    Subscription sub2=new Subscription(date2,sub_plan2);
    Subscription sub3=new Subscription(date3,sub_plan3);
    Subscription sub4=new Subscription(date4,sub_plan4);
    
    @Test
    public void TestGetSubscriptionStartDate(){
        Date expect1=date1;
        Date expect2=date2;
        Date expect3=date3;
        Date expect4=date4;
        assertEquals(expect1,sub1.getSubscriptionStartDate());
        assertEquals(expect2,sub2.getSubscriptionStartDate());
        assertEquals(expect3,sub3.getSubscriptionStartDate());
        assertEquals(expect4,sub4.getSubscriptionStartDate());
    }
    
    @Test
    public void TestSetSubscriptionStartDate(){
        sub1.setSubscriptionStartDate(date2);
        sub2.setSubscriptionStartDate(date3);
        sub3.setSubscriptionStartDate(date4);
        sub4.setSubscriptionStartDate(date1);
        Date expect1=date2;
        Date expect2=date3;
        Date expect3=date4;
        Date expect4=date1;
        assertEquals(expect1,sub1.getSubscriptionStartDate());
        assertEquals(expect2,sub2.getSubscriptionStartDate());
        assertEquals(expect3,sub3.getSubscriptionStartDate());
        assertEquals(expect4,sub4.getSubscriptionStartDate());
    }
    
    @Test
    public void TestGetSubscriptionPlan(){
        SubscriptionPlan expect1=sub_plan1;
        SubscriptionPlan expect2=sub_plan2;
        SubscriptionPlan expect3=sub_plan3;
        SubscriptionPlan expect4=sub_plan4;
        assertEquals(expect1,sub1.getSubscriptionPlan());
        assertEquals(expect2,sub2.getSubscriptionPlan());
        assertEquals(expect3,sub3.getSubscriptionPlan());
        assertEquals(expect4,sub4.getSubscriptionPlan());
    }
    
    @Test
    public void TestSetSubscriptionPlan(){
        sub1.setSubscriptionPlan(sub_plan2);
        sub2.setSubscriptionPlan(sub_plan3);
        sub3.setSubscriptionPlan(sub_plan4);
        sub4.setSubscriptionPlan(sub_plan1);
        SubscriptionPlan expect1=sub_plan2;
        SubscriptionPlan expect2=sub_plan3;
        SubscriptionPlan expect3=sub_plan4;
        SubscriptionPlan expect4=sub_plan1;
        assertEquals(expect1,sub1.getSubscriptionPlan());
        assertEquals(expect2,sub2.getSubscriptionPlan());
        assertEquals(expect3,sub3.getSubscriptionPlan());
        assertEquals(expect4,sub4.getSubscriptionPlan());
    }
    
}
