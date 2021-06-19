
package nesne.proje;

import static junit.framework.Assert.assertEquals;
import org.junit.Test;
import org.junit.*;

public class TestSubscriptionPlan {
    
    ServiceProvider gsm_provider1=new GSMProvider("GSM Provider-1");
    ServiceProvider cable_provider1=new CableProvider("Cable Provider-1");
    
    SubscriptionPlan sub_plan1=new SubscriptionPlan("Subscription Plan-1");
    SubscriptionPlan sub_plan2=new SubscriptionPlan("Subscription Plan-2",gsm_provider1);
    SubscriptionPlan sub_plan3=new SubscriptionPlan("Subscription Plan-3");
    SubscriptionPlan sub_plan4=new SubscriptionPlan("Subscription Plan-4",cable_provider1);
    
    @Test
    public void TestGetName(){
        String expect1="Subscription Plan-1";
        String expect2="Subscription Plan-2";
        String expect3="Subscription Plan-3";
        String expect4="Subscription Plan-4";
        assertEquals(expect1,sub_plan1.getName());
        assertEquals(expect2,sub_plan2.getName());
        assertEquals(expect3,sub_plan3.getName());
        assertEquals(expect4,sub_plan4.getName());
    }
    
    @Test
    public void TestSetName(){
        sub_plan1.setName("Subscription Plan-01");
        sub_plan2.setName("Subscription Plan-02");
        sub_plan3.setName("Subscription Plan-03");
        sub_plan4.setName("Subscription Plan-04");
        String expect1="Subscription Plan-01";
        String expect2="Subscription Plan-02";
        String expect3="Subscription Plan-03";
        String expect4="Subscription Plan-04";
        assertEquals(expect1,sub_plan1.getName());
        assertEquals(expect2,sub_plan2.getName());
        assertEquals(expect3,sub_plan3.getName());
        assertEquals(expect4,sub_plan4.getName());
    }
    
    @Test
    public void TestGetServiceProvider(){
        ServiceProvider expect1=null;
        ServiceProvider expect2=gsm_provider1;
        ServiceProvider expect3=null;
        ServiceProvider expect4=cable_provider1;
        assertEquals(expect1,sub_plan1.getServiceProvider());
        assertEquals(expect2,sub_plan2.getServiceProvider());
        assertEquals(expect3,sub_plan3.getServiceProvider());
        assertEquals(expect4,sub_plan4.getServiceProvider());
    }
    
    @Test
    public void TestSetServiceProvider(){
        sub_plan1.setServiceProvider(gsm_provider1);
        sub_plan2.setServiceProvider(cable_provider1);
        sub_plan3.setServiceProvider(cable_provider1);
        sub_plan4.setServiceProvider(gsm_provider1);
        ServiceProvider expect1=gsm_provider1;
        ServiceProvider expect2=cable_provider1;
        ServiceProvider expect3=cable_provider1;
        ServiceProvider expect4=gsm_provider1;
        assertEquals(expect1,sub_plan1.getServiceProvider());
        assertEquals(expect2,sub_plan2.getServiceProvider());
        assertEquals(expect3,sub_plan3.getServiceProvider());
        assertEquals(expect4,sub_plan4.getServiceProvider());
    }
    
    
}
