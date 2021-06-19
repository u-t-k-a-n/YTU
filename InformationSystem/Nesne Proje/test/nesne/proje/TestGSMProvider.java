
package nesne.proje;

import static junit.framework.Assert.assertEquals;
import org.junit.Test;
import org.junit.*;

public class TestGSMProvider {
    ServiceProvider gsm_provider1=new GSMProvider("GSM Provider-1");
    ServiceProvider cable_provider1=new CableProvider("Cable Provider-1");
    GSMProvider gsm_provider2=new GSMProvider("GSM Provider-2");
    
    SubscriptionPlan sub_plan1=new SubscriptionPlan("Subscription Plan-1");
    SubscriptionPlan sub_plan2=new SubscriptionPlan("Subscription Plan-2",gsm_provider1);
    SubscriptionPlan sub_plan3=new SubscriptionPlan("Subscription Plan-3");
    SubscriptionPlan sub_plan4=new SubscriptionPlan("Subscription Plan-4",cable_provider1);
    
    @Test
    public void TestAddSubscriptionPlan(){
        gsm_provider1.addSubscriptionPlan(sub_plan1);
        gsm_provider1.addSubscriptionPlan(sub_plan2);
        gsm_provider1.addSubscriptionPlan(sub_plan3);
        gsm_provider1.addSubscriptionPlan(sub_plan4);
        
        gsm_provider2.addSubscriptionPlan(sub_plan1);
        gsm_provider2.addSubscriptionPlan(sub_plan2);
        gsm_provider2.addSubscriptionPlan(sub_plan3);
        gsm_provider2.addSubscriptionPlan(sub_plan4);
        
        SubscriptionPlan expect1=sub_plan1;
        SubscriptionPlan expect2=sub_plan2;
        SubscriptionPlan expect3=sub_plan3;
        SubscriptionPlan expect4=sub_plan4;
        
        assertEquals(expect1,gsm_provider1.findSubscriptionPlan(expect1.getName()));
        assertEquals(expect2,gsm_provider1.findSubscriptionPlan(expect2.getName()));
        assertEquals(expect3,gsm_provider1.findSubscriptionPlan(expect3.getName()));
        assertEquals(expect4,gsm_provider1.findSubscriptionPlan(expect4.getName()));
        
        assertEquals(expect1,gsm_provider2.findSubscriptionPlan(expect1.getName()));
        assertEquals(expect2,gsm_provider2.findSubscriptionPlan(expect2.getName()));
        assertEquals(expect3,gsm_provider2.findSubscriptionPlan(expect3.getName()));
        assertEquals(expect4,gsm_provider2.findSubscriptionPlan(expect4.getName()));
    }
    
    @Test
    public void TestGetName(){
        String expect1="GSM Provider-1";
        String expect2="GSM Provider-2";
        assertEquals(expect1,gsm_provider1.getName());
        assertEquals(expect2,gsm_provider2.getName());
    }
    
    @Test
    public void TestSetName(){
        gsm_provider1.setName("GSM Provider-01");
        gsm_provider2.setName("GSM Provider-02");
        String expect1="GSM Provider-01";
        String expect2="GSM Provider-02";
        assertEquals(expect1,gsm_provider1.getName());
        assertEquals(expect2,gsm_provider2.getName());
    }
    
}
