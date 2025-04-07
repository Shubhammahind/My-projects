import java.net.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

class Server {
    private static final SimpleDateFormat LOG_DATE_FORMAT = new SimpleDateFormat("yyyyMMdd_HHmmss");
    private static final SimpleDateFormat CHAT_DATE_FORMAT = new SimpleDateFormat("HH:mm:ss");
    private static PrintWriter logWriter;
    
    public static void main(String[] args) throws Exception {
        setupLogging();
        
        System.out.println("Server application is running...");
        log("Server started");

        ServerSocket ssobj = new ServerSocket(2100);
        log("Server waiting on port 2100");

        Socket sobj = ssobj.accept();
        log("Client connected: " + sobj.getInetAddress());

        PrintStream ps = new PrintStream(sobj.getOutputStream()); 
        BufferedReader br1 = new BufferedReader(new InputStreamReader(sobj.getInputStream()));
        BufferedReader br2 = new BufferedReader(new InputStreamReader(System.in));
        
        String str1, str2;
        log("Chat session started");
        
        while((str1 = br1.readLine()) != null) {
            String timestamp = CHAT_DATE_FORMAT.format(new Date());
            String clientMsg = "[" + timestamp + "] Client: " + str1;
            System.out.println(clientMsg);
            log(clientMsg);
            
            if(str1.equalsIgnoreCase("end")) {
                break;
            }
            
            System.out.print("Enter message for client: ");
            str2 = br2.readLine();
            
            String serverMsg = "[" + timestamp + "] Server: " + str2;
            ps.println(str2);
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