// JCount.java

/*
 Basic GUI/Threading exercise.
*/

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class JCount extends JPanel {
	private JTextField textField;
	private JLabel countLabel;
	private JButton startButton;
	private JButton endButton;

	Worker worker;
	public JCount() {
		// Set the JCount to use Box layout
		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				createAndShowGUI();
			}
		});
	}

	private void createAndShowGUI() {
		textField = new JTextField(100);
		add(textField);
		countLabel = new JLabel("0");
		add(countLabel);
		startButton = new JButton("Start");
		add(startButton);
		endButton = new JButton("End");
		add(endButton);
		add(Box.createRigidArea(new Dimension(0,40)));
		addListeners();
	}

	private void addListeners() {
		startButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(worker != null && worker.isAlive())
					worker.interrupt();
				worker = new Worker(Integer.parseInt(textField.getText()));
				worker.start();
			}
		});
		endButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if(worker != null && worker.isAlive())
					worker.interrupt();
			}
		});
	}


	static public void main(String[] args)  {
		// Creates a frame with 4 JCounts in it.
		// (provided)
		JFrame frame = new JFrame("The Count");
		frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));

		frame.add(new JCount());
		frame.add(new JCount());
		frame.add(new JCount());
		frame.add(new JCount());

		frame.setSize(200, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}

	private class Worker extends Thread{
		int target;
		public Worker(int target){
			this.target = target;
		}
		//pirobashi gaurkvevlad ewera stopze ra unda meqna
		//tu sachiro iqneboda bolo ricxvi dametovebina labelze
		//ubralod breakebis win invoke rom miweria amovshlidi
		//da runis dasawyisshi davwerdi 1-xel da vsio
		public void run() {
			int curr = 0;
			while(curr <= target){
				if (isInterrupted()) {
					SwingUtilities.invokeLater(new Runnable() {
						public void run() {
							countLabel.setText("0");
						}
					});
					break;
				}
				if(curr % 10000 == 0){
					int finalCurr = curr;
					SwingUtilities.invokeLater(new Runnable() {
						public void run() {
							countLabel.setText(Integer.toString(finalCurr));
						}
					});
					try {
						Thread.sleep(100);
					} catch (InterruptedException ignored) {
						SwingUtilities.invokeLater(new Runnable() {
							public void run() {
								countLabel.setText("0");
							}
						});
						break;
					}
				}
				curr++;
			}
		}
	}
}

