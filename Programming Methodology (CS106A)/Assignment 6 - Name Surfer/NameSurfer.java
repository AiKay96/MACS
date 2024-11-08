
/*
 * File: NameSurfer.java
 * ---------------------
 * When it is finished, this program will implements the viewer for
 * the baby-name database described in the assignment handout.
 */

import acm.program.*;
import java.awt.event.*;
import javax.swing.*;

public class NameSurfer extends Program implements NameSurferConstants {

	/* Method: init() */
	/**
	 * This method has the responsibility for reading in the data base and
	 * initializing the interactors at the bottom of the window.
	 */
	public void init() {
		setSize(APPLICATION_WIDTH, APPLICATION_HEIGHT);
		addButtons();
		graph = new NameSurferGraph();
		add(graph);
	}

	/* Method: addButtons() */
	/** Method to add all buttons at south */
	private void addButtons() {
		name = new JLabel("Name");
		add(name, SOUTH);
		field = new JTextField(10);
		field.addActionListener(this);
		add(field, SOUTH);
		graphButton = new JButton("Graph");
		graphButton.addActionListener(this);
		add(graphButton, SOUTH);
		clearButton = new JButton("Clear");
		clearButton.addActionListener(this);
		add(clearButton, SOUTH);
	}

	/* Method: actionPerformed(e) */
	/**
	 * This class is responsible for detecting when the buttons are clicked, so you
	 * will have to define a method to respond to button actions.
	 */
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == graphButton || e.getSource() == field) {
			NameSurferEntry entry = data.findEntry(nameCorrect(field.getText()));
			graph.addEntry(entry);
		}
		if (e.getSource() == clearButton) {
			graph.clear();
		}
	}

	/* Method: nameCorrect(name) */
	/**
	 * Method that checks our spelling. name should start with big characters and
	 * end with small ones
	 */
	private String nameCorrect(String name) {
		char c = name.charAt(0);
		/** checks first char */
		if (c >= 'a' && c <= 'z') {
			c -= 'a';
			c += 'A';
		}
		String correctedName = c + "";
		/** checks another chars */
		for (int i = 1; i < name.length(); i++) {
			char ch = name.charAt(i);
			if (ch >= 'A' && ch <= 'Z') {
				ch -= 'A';
				ch += 'a';
			}
			correctedName += ch;
		}
		return correctedName;
	}

	private NameSurferDataBase data = new NameSurferDataBase(NAMES_DATA_FILE);
	private NameSurferGraph graph;
	private JLabel name;
	private JTextField field;
	private JButton graphButton;
	private JButton clearButton;
}
