
package nesne.proje;


public class ExistingCustomer extends Customer {
    private Subscription subscription;
    
     public ExistingCustomer(String CitizenshipNr) {
        super(CitizenshipNr);
    }

    public ExistingCustomer(String CitizenshipNr,Subscription subscription) {
        super(CitizenshipNr);
        this.subscription = subscription;
    }

    public Subscription getSubscription() {
        return subscription;
    }

    public void setSubscription(Subscription subscription) {
        this.subscription = subscription;
    }
    
    
    
    
    
}
