import com.sun.deploy.net.MessageHeader;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.Semaphore;

public class WebFrame extends JFrame {
    boolean interrupted;
    private Launcher launcher;
    private WebFrame currFrame;
    Integer count;
    Integer complete;
    private long elapsedT;
    public String fileName;
    DefaultTableModel model;
    private JTable table;
    private JPanel panel;
    private JButton singleButton;
    private JButton concurButton;
    private JTextField textField;
    private JLabel running;
    private JLabel completed;
    private JLabel elapsed;
    private JProgressBar bar;
    private JButton stopButton;
    public WebFrame(String fileName){
        super("WebLoader");

        this.fileName = fileName;
        count = 0;
        complete = 0;
        currFrame = this;
        setUpFrame();
        makeTable();
        addButtons();
        addListeners();
    }

    private void addListeners() {
        singleButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                reset();
                launcher = new Launcher(currFrame, 1);
                launcher.start();
            }
        });
        concurButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                reset();
                launcher = new Launcher(currFrame, Integer.parseInt(textField.getText()));
                launcher.start();
            }
        });
        stopButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(launcher != null && launcher.isAlive())
                    launcher.interrupt();
            }
        });
    }

    private void reset() {
        interrupted = false;
        running.setText("Running: ");
        completed.setText("Completed: ");
        elapsed.setText("Elapsed");
        bar.setValue(0);
        for(int i = 0; i < model.getRowCount(); i++)
            model.setValueAt("", i, 1);
    }

    private void addButtons() {
        singleButton = new JButton("Single Thread Fetch");
        singleButton.setMaximumSize(new Dimension(200, 50));
        panel.add(singleButton);
        concurButton = new JButton("Concurrent Fetch");
        concurButton.setMaximumSize(new Dimension(200, 50));
        panel.add(concurButton);
        textField = new JTextField();
        textField.setMaximumSize(new Dimension(200, 50));
        panel.add(textField);
        running = new JLabel("Running: 0");
        completed = new JLabel("Completed: 0");
        elapsed = new JLabel("Elapsed");
        panel.add(running);
        panel.add(completed);
        panel.add(elapsed);
        bar = new JProgressBar();
        bar.setMaximum(model.getRowCount());
        panel.add(bar);
        stopButton = new JButton("Stop");
        stopButton.setEnabled(false);
        stopButton.setMaximumSize(new Dimension(200, 50));
        panel.add(stopButton);
    }

    private void setUpFrame() {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        panel = new JPanel();
        this.add(panel);
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
    }

    private void makeTable(){
        model = new DefaultTableModel(new String[] { "url", "status"}, 0);
        table = new JTable(model);
        table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
        JScrollPane scrollpane = new JScrollPane(table);
        scrollpane.setPreferredSize(new Dimension(600,300));
        panel.add(scrollpane);

        try{
            BufferedReader bf = new BufferedReader(new FileReader(new File(fileName)));
            while(true){
                String cur = bf.readLine();
                if(cur==null){
                    break;
                }
                model.addRow(new String[]{cur});
            }
            bf.close();
        }catch(IOException ignored){
        }
    }

    public static void main(String[] args){
        if(args.length != 1){
            System.out.println("Program Arguments: urls-file-name");
            return;
        }
        WebFrame frame = new WebFrame(args[0]);
        frame.setSize(600, 600);
        frame.setVisible(true);
    }

    class Launcher extends Thread{
        int maxNum;
        Semaphore launcherSem;
        ArrayList<WebWorker> workers;
        WebFrame frame;
        public Launcher(WebFrame frame, int num){
            this.frame = frame;
            maxNum = num;
            launcherSem = new Semaphore(maxNum);
            workers = new ArrayList<>();
        }

        @Override
        public void run() {
            long start = System.currentTimeMillis();
            returnButtons(false);
            count = 1;
            complete = 0;
            updateRunningLabel();
            for(int i =0; i < model.getRowCount(); i++){
                try {
                    launcherSem.acquire();
                    synchronized (count) {
                        count++;
                    }
                    updateRunningLabel();
                    WebWorker worker = new WebWorker(i, frame, this);
                    workers.add(worker);
                    worker.start();
                } catch (InterruptedException e) {
                    stopWorkers();
                    synchronized (count) {
                        count = 1;
                    }
                    updateRunningLabel();
                    returnButtons(true);
                    elapsedT = System.currentTimeMillis() - start;
                    updateElapsedLabel();
                    break;
                }
            }
            try {
                launcherSem.acquire(maxNum);
                synchronized (count) {
                    count = 0;
                }
                updateRunningLabel();
                returnButtons(true);
                elapsedT = System.currentTimeMillis() - start;
                updateElapsedLabel();
            } catch (InterruptedException ignored) {
                stopWorkers();
                synchronized (count) {
                    count = 0;
                }
                updateRunningLabel();
                returnButtons(true);
                elapsedT = System.currentTimeMillis() - start;
                updateElapsedLabel();
            }
        }
        private void updateElapsedLabel() {
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    updateElapsed();
                }
            });
        }

        void updateRunningLabel() {
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    updateRunning();
                }
            });
        }

        private void returnButtons(boolean isStarting){
            SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {
                    buttonStartingPosition(isStarting);
                }
            });
        }

        private void stopWorkers() {
            interrupted = true;
            for(int i = 0; i < workers.size(); i++){
                WebWorker curr = workers.get(i);
                if(curr != null && curr.isAlive())
                    curr.interrupt();
            }
            interrupt();
        }
    }
    void updateCompleted() {
        completed.setText("Completed: " + complete);
        bar.setValue(complete);
    }

    private void updateElapsed() {
        elapsed.setText("Elapsed: " + elapsedT);
    }

    private void buttonStartingPosition(boolean isStarting) {
        singleButton.setEnabled(isStarting);
        concurButton.setEnabled(isStarting);
        stopButton.setEnabled(!isStarting);
        if(isStarting)
            bar.setValue(0);
    }
    void updateRunning(){
        running.setText("Running: " + count);
    }
}
