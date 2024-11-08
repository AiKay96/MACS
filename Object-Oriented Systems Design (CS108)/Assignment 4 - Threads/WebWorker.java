import java.io.*;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.*;

public class WebWorker extends Thread {
    WebFrame frame;
    WebFrame.Launcher launcher;
    int ind;
    String urlString;
    String status;
    public WebWorker(int ind, WebFrame frame, WebFrame.Launcher launcher){
        this.ind = ind;
        this.frame = frame;
        this.launcher = launcher;
        urlString = (String)frame.model.getValueAt(ind,0);
    }

    @Override
    public void run() {
        download();
        frame.updateRunning();
        frame.model.setValueAt(status, ind, 1);
        synchronized (frame.count){
            if(!frame.interrupted)
                frame.count--;
        }
        synchronized (frame.complete){
            frame.complete++;
        }
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                frame.updateCompleted();
            }
        });
        launcher.updateRunningLabel();
        launcher.launcherSem.release();
    }

    private void download() {
        InputStream input = null;
        StringBuilder contents = null;
        try {
            URL url = new URL(urlString);
            URLConnection connection = url.openConnection();

            // Set connect() to throw an IOException
            // if connection does not succeed in this many msecs.
            connection.setConnectTimeout(5000);

            connection.connect();
            input = connection.getInputStream();

            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            long start = System.currentTimeMillis();
            int numBytes = 0;
            char[] array = new char[1000];
            int len;
            contents = new StringBuilder(1000);
            while ((len = reader.read(array, 0, array.length)) > 0) {
                contents.append(array, 0, len);
                Thread.sleep(100);
                numBytes += len;
            }
            // Successful download if we get here
            status = (new SimpleDateFormat("HH:MM:SS").format(new Date(start))) + " "
                    + (System.currentTimeMillis() - start) + "ms " + numBytes + "bytes.";
        }
        // Otherwise control jumps to a catch...
        catch (MalformedURLException ignored) {
            status = "err";
        } catch (InterruptedException exception) {
            // YOUR CODE HERE
            // deal with interruption
            status = "err";
        } catch (IOException ignored) {
            status = "err";
        }
        // "finally" clause, to close the input stream
        // in any case
        finally {
            try {
                if (input != null) input.close();
            } catch (IOException ignored) {
            }
        }
    }
}
