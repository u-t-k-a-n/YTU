
package nesne.proje;

import java.util.ArrayList;


class GSMProvider implements ServiceProvider {
    private String name;
    private ArrayList<SubscriptionPlan> subscriptionPlans;


    public GSMProvider(String name) {
        this.name = name;
        this.subscriptionPlans = new ArrayList<SubscriptionPlan>();
    }
    

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    
    public void addSubscriptionPlan(SubscriptionPlan subscriptionPlan){
        subscriptionPlans.add(subscriptionPlan);
    }
    
    public SubscriptionPlan findSubscriptionPlan(String name){
        //return the object if in subscriptionPlans else null
        for (SubscriptionPlan i:subscriptionPlans){
            if (i.getName().equals(name)){
                return i;
            }
        }
        return null;
    }
   
}
