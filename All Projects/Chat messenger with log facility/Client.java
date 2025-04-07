import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

class Client {
    private static final SimpleDateFormat LOG_DATE_FORMAT = new SimpleDateFormat("yyyyMMdd_HHmmss");
    private static final SimpleDateFormat CHAT_DATE_FORMAT = new SimpleDateFormat("HH:mm:ss");
    private static PrintWriter logWriter;
    
    public static void main(String[] args) throws Exception {
        setupLogging();
        
        System.out.println("Client application is running...");
        log("Client started");

        Socket sobj = new Socket("localhost", 2100);
        log("Connected to server");

        PrintStream ps = new PrintStream(sobj.getOutputStream()); 
        BufferedReader br1 = new BufferedReader(new InputStreamReader(sobj.getInputStream()));
        BufferedReader br2 = new BufferedReader(new InputStreamReader(System.in));
        
        String str1, str2;
        log("Chat session started");
        
        while(true) {
            System.out.print("Enter message (type 'end' to quit): ");
            str1 = br2.readLine();
            
            String timestamp = CHAT_DATE_FORMAT.format(new Date());
            String clientMsg = "[" + timestamp + "] You: " + str1;
            log(clientMsg);
            
            ps.println(str1);
            
            if(str1.equalsIgnoreCase("end")) {
                break;
            }
            
            str2 = br1.readLine();
            String serverMsg = "[" + timestamp + "] Server: " + str2;
            System.out.println(serverMsg);
            log(serverMsg);
        }
        
        log("Chat session ended");
        closeLogging();
        System.out.println("Thank you for using the Chat Application..");
    }
    
    private static void setupLogging() throws IOException {
        String logFileName = "chat_log_" + LOG_DATE_FORMAT.format(new Date()) + ".txt";
        logWriter = new PrintWriter(new FileWriter(logFileName, true));
    }
    
    private static void log(String message) {
        logWriter.println(message);
        logWriter.flush();
    }
    
    private static void closeLogging() {
        if(logWriter != null) {
            logWriter.close();
        }
    }
}