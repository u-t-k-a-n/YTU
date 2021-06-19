
package nesne.proje;

import java.text.ParseException;
import java.util.Scanner;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.InputMismatchException;

public class InformationSystem {


    public static void main(String[] args) {
        Scanner input=new Scanner(System.in);
        int number_sub_plan;
        
        System.out.print("GSM SERVICE PROVIDER? :  ");
        String gsm_provider_name=input.next();
        
        //avoiding any string
        while (true){
            try{
                System.out.print("NUMBER OF SUBSCRIPTION PLANS? : ");
                number_sub_plan=input.nextInt();
                break;
            }
            catch(InputMismatchException e){
                System.out.println("PLEASE ENTER AN INTEGER!!!!");
            }
            input.nextLine();//refreshing input
        }
        
        //expecting an integer greater than 0
        while (number_sub_plan<1){
            System.out.println("PLEASE ENTER AN INTEGER GREATER THAN ONE!!!!!");
            //avoiding any string
            while (true){
            
                try{
                    System.out.print("NUMBER OF SUBSCRIPTION PLANS? : ");
                    number_sub_plan=input.nextInt();
                    break;
                }
                catch(InputMismatchException e){
                    System.out.println("PLEASE ENTER AN INTEGER!!!!");
                }
                input.nextLine();//refreshing input
            } 
        }
        
        ServiceProvider gsm_provider1=new GSMProvider(gsm_provider_name);
        
        for (int i=0;i<number_sub_plan;i++){
            
            System.out.print("NAME OF THE Plan #"+i+" ?:  ");
            String sub_plan_name=input.next();
            SubscriptionPlan sub_plan1=new SubscriptionPlan(sub_plan_name,gsm_provider1);
            gsm_provider1.addSubscriptionPlan(sub_plan1);
        }
                
        System.out.print("CUSTOMER CITIZENSHIP NUMBER ? : ");
        String citizenship_number=input.next();
        System.out.print("CUSTOMER NAME ? :  ");
        String customer_name=input.next();
        
        PossibleCustomer customer1=new PossibleCustomer(citizenship_number);
        customer1.setName(customer_name);
        
        System.out.print("NAME OF THE PLAN TO BE SUBSCRIBED ? : ");
        String to_be_subs=input.next();
        
        SubscriptionPlan wanting_subPlan;
        

        wanting_subPlan=gsm_provider1.findSubscriptionPlan(to_be_subs);
        //expecting an existing subscription plan
        while (wanting_subPlan==null){
            System.out.println("THERE IS NO SUBSCRIPTION PLAN NAMED "+to_be_subs);
            System.out.print("NAME OF THE PLAN TO BE SUBSCRIBED ? : ");
            to_be_subs=input.next();
            wanting_subPlan=gsm_provider1.findSubscriptionPlan(to_be_subs);
        }
        
        
        System.out.print("START DATE FOR SUBSCRIPTION (MM/DD/YYYY)? : ");
        String start_date_subs=input.next();
        SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
        Date date1=null;
        
        //expecting a date in the proper format
        while (true){
            try {
                date1 = dateFormat.parse(start_date_subs);
                break;
            } 
            catch (ParseException e) {
                System.out.println("PLEASE ENTER THE DATE IN PROPER FORMAT (MM/DD/YYYY)!!!!!");
                System.out.print("START DATE FOR SUBSCRIPTION (MM/DD/YYYY)? : ");
                start_date_subs=input.next();
            }
        }
        
        Subscription sub1=new Subscription(date1,wanting_subPlan);
        ExistingCustomer exist_customer1=new ExistingCustomer(customer1.getCitizenshipNr(),sub1);
        exist_customer1.setName(customer1.getName());
        customer1=null;//not using anymore
        
        System.out.println("-----------------------------------------------------");
        System.out.println("CUSTOMER CITIZENSHIP NUMBER = "+exist_customer1.getCitizenshipNr());
        System.out.println("CUSTOMER NAME = "+exist_customer1.getName());
        System.out.println("SERVICE PROVIDER : "+exist_customer1.getSubscription().getSubscriptionPlan().getServiceProvider().getName());
        
        date1=exist_customer1.getSubscription().getSubscriptionStartDate();
        String print_date=dateFormat.format(date1);
        
        System.out.println("SUBSCRIPTION START DATE : "+print_date);
        System.out.println("SUBSCRIPTION PLAN NAME : "+exist_customer1.getSubscription().getSubscriptionPlan().getName());
        System.out.println("-----------------------------------------------------");
    }
    
}
