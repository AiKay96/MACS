import javax.swing.*;
import javax.swing.border.TitledBorder;
import javax.swing.event.*;

import java.awt.*;
import java.awt.event.*;


 public class SudokuFrame extends JFrame {
	JPanel panel;
	JPanel rightPanel;
	JPanel leftPanel;
	JTextArea source;
	JTextArea answer;
	JPanel miniPanel;
	JButton button;
	JCheckBox checkBox;

	public SudokuFrame() {
		super("Sudoku Solver");
		panel = new JPanel();
		panel.setLayout(new BorderLayout(4, 4));
		//right side
		rightPanel = new JPanel();
		rightPanel.setLayout(new BoxLayout(rightPanel, BoxLayout.Y_AXIS));
		source = new JTextArea(15, 20);
		rightPanel.add(source);
		rightPanel.setBorder(new TitledBorder("Puzzle"));
		panel.add(rightPanel, BorderLayout.CENTER);
		//left side
		leftPanel = new JPanel();
		leftPanel.setLayout(new BoxLayout(leftPanel, BoxLayout.Y_AXIS));
		answer = new JTextArea(15, 20);
		leftPanel.add(answer);
		leftPanel.setBorder(new TitledBorder("Solution"));
		panel.add(leftPanel, BorderLayout.EAST);
		//buttons side
		miniPanel = new JPanel();
		miniPanel.setLayout(new BoxLayout(miniPanel, BoxLayout.X_AXIS));
		button = new JButton("Check");
		miniPanel.add(button);
		checkBox = new JCheckBox("Auto Check");
		miniPanel.add(checkBox);
		panel.add(miniPanel, BorderLayout.SOUTH);

		add(panel);
		addingListeners();
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
		setVisible(true);
	}
	private void frameSolver(){
		Sudoku sudoku = new Sudoku(Sudoku.textToGrid(source.getText()));
		int count = sudoku.solve();
		long ms = sudoku.getElapsed();
		String ans = sudoku.getSolutionText();
		ans += "\n";
		ans += "solutions: ";
		ans += count;
		ans += "\n";
		ans += "elapsed: ";
		ans += ms;
		ans += "ms\n";
		answer.setText(ans);
	}
	private void addingListeners(){
		button.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				frameSolver();
			}
		});
		source.getDocument().addDocumentListener(new DocumentListener() {
			@Override
			public void insertUpdate(DocumentEvent e) {
				try{
					if(checkBox.isSelected())
						frameSolver();
				}catch (Exception ex){
					answer.setText("Parsing Problem.");
				}
			}

			@Override
			public void removeUpdate(DocumentEvent e) {
				try{
					if(checkBox.isSelected())
						frameSolver();
				}catch (Exception ex){
					answer.setText("Parsing Problem.");
				}
			}

			@Override
			public void changedUpdate(DocumentEvent e) {
				try{
					if(checkBox.isSelected())
						frameSolver();
				}catch (Exception ex){
					answer.setText("Parsing Problem.");
				}
			}
		});
	}
	
	public static void main(String[] args) {
		// GUI Look And Feel
		// Do this incantation at the start of main() to tell Swing
		// to use the GUI LookAndFeel of the native platform. It's ok
		// to ignore the exception.
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception ignored) { }
		
		SudokuFrame frame = new SudokuFrame();
	}

}
