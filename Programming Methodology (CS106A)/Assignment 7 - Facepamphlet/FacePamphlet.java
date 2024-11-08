
/* 
 * File: FacePamphlet.java
 * -----------------------
 * When it is finished, this program will implement a basic social network
 * management system.
 */

import acm.program.*;
import acm.graphics.*;
import acm.util.*;
import java.awt.event.*;
import javax.swing.*;

public class FacePamphlet extends Program implements FacePamphletConstants {

	/**
	 * This method has the responsibility for initializing the interactors in the
	 * application, and taking care of any other initialization that needs to be
	 * performed.
	 */
	public void init() {
		setSize(APPLICATION_WIDTH, APPLICATION_HEIGHT);
		addButtons();
		canvas = new FacePamphletCanvas();
		add(canvas);
	}

	/**
	 * This class is responsible for detecting when the buttons are clicked or
	 * interactors are used, so you will have to add code to respond to these
	 * actions.
	 */
	public void actionPerformed(ActionEvent e) {
		// If "Add" button is clicked
		if (e.getSource() == addButton) {
			String addName = nameField.getText();
			// If entered name isn't empty
			if (!addName.equals("")) {
				// If profile already exists
				if (profileDataBase.containsProfile(addName)) {
					// only changing current profile
					profile = profileDataBase.getProfile(addName);
					canvas.showMessage("A profile with the name " + addName + " already exists");

				} else {
					// creating new profile and make it current one
					profile = new FacePamphletProfile(addName);
					profileDataBase.addProfile(profile);
					canvas.showMessage("New profile created");
				}
			}
		}
		// If "Delete" button is clicked
		if (e.getSource() == deleteButton) {
			String deleteName = nameField.getText();
			// If entered name isn't empty
			if (!deleteName.equals("")) {
				// If profile exists
				if (profileDataBase.containsProfile(deleteName)) {
					// deleting it from dataBase
					profileDataBase.deleteProfile(deleteName);
					canvas.showMessage("Profile of " + deleteName + " deleted");
				} else {
					canvas.showMessage("A profile with the name " + deleteName + " doesn't exists");
				}
				// make current profile null
				profile = null;
			}
		}
		// If "LookUp" button is clicked
		if (e.getSource() == lookUpButton) {
			String lookUpName = nameField.getText();
			// If entered name isn't empty
			if (!lookUpName.equals("")) {
				// If profile exists
				if (profileDataBase.containsProfile(lookUpName)) {
					// changing current profile
					profile = profileDataBase.getProfile(lookUpName);
					canvas.showMessage("Displaying " + lookUpName);
				} else {
					// make current profile null
					profile = null;
					canvas.showMessage("A profile with the name " + lookUpName + " doesn't exists");
				}
			}
		}
		// If "Change Status" button or enter clicked
		if (e.getSource() == changeStatusButton || e.getSource() == changeStatusField) {
			String status = changeStatusField.getText();
			// If entered status isn't empty
			if (!status.equals("")) {
				// If current profile isn't null
				if (profile != null) {
					// Changing status for current profile
					profile.setStatus(status);
					canvas.showMessage("Status updated to " + status);
				} else {
					canvas.showMessage("Please select a profile to change status");
				}
			}
		}
		// If "Change Picture" button or enter clicked
		if (e.getSource() == changePictureButton || e.getSource() == changePictureField) {
			// If entered file name isn't empty
			if (!changePictureField.getText().equals("")) {
				// If current profile isn't null
				if (profile != null) {
					String imageName = changePictureField.getText();
					GImage image = null;
					// If imageName is correct changes profile picture
					try {
						image = new GImage(imageName);
						profile.setImage(image);
						canvas.showMessage("Picture updated");
					} catch (ErrorException ex) {

					}
					// If imageName is incorrect
					if (image == null) {
						canvas.showMessage("Unable to open image file: " + imageName);
					}
				} else {
					canvas.showMessage("Please select a profile to change picture");
				}
			}
		}
		// If "Add Friend" button or enter is clicked
		if (e.getSource() == addFriendButton || e.getSource() == addFriendField) {
			String friendName = addFriendField.getText();
			// If entered name isn't empty
			if (!friendName.equals("")) {
				// If current profile isn't null
				if (profile != null) {
					// If entered profile exists
					if (profileDataBase.containsProfile(friendName)) {
						// If entered profile isn't you
						if (profile.getName().equals(friendName)) {
							canvas.showMessage("You can't add yourself as friend");
						} else if (profile.addFriend(friendName)) {
							// Adds in friends list for both
							profile.addFriend(friendName);
							FacePamphletProfile friend = profileDataBase.getProfile(friendName);
							friend.addFriend(profile.getName());
							canvas.showMessage(friendName + " added as friend");
						} else {
							canvas.showMessage(profile.getName() + " already has " + friendName + " as a friend");
						}
					} else {
						canvas.showMessage(friendName + " does not exist");
					}
				} else {
					canvas.showMessage("Please select a profile to add friend");
				}
			}
		}
		canvas.displayProfile(profile);
	}

	/** method to add buttons */
	private void addButtons() {
		/** North buttons and fields */

		nameLabel = new JLabel("Name");
		add(nameLabel, NORTH);

		nameField = new JTextField(TEXT_FIELD_SIZE);
		add(nameField, NORTH);

		addButton = new JButton("Add");
		addButton.addActionListener(this);
		add(addButton, NORTH);

		deleteButton = new JButton("Delete");
		deleteButton.addActionListener(this);
		add(deleteButton, NORTH);

		lookUpButton = new JButton("LookUp");
		lookUpButton.addActionListener(this);
		add(lookUpButton, NORTH);

		/** West buttons and fields */
		changeStatusField = new JTextField(TEXT_FIELD_SIZE);
		changeStatusField.addActionListener(this);
		add(changeStatusField, WEST);

		changeStatusButton = new JButton("Change Status");
		changeStatusButton.addActionListener(this);
		add(changeStatusButton, WEST);

		emptyLabel1 = new JLabel(EMPTY_LABEL_TEXT);
		add(emptyLabel1, WEST);

		changePictureField = new JTextField(TEXT_FIELD_SIZE);
		changePictureField.addActionListener(this);
		add(changePictureField, WEST);

		changePictureButton = new JButton("Change Picture");
		changePictureButton.addActionListener(this);
		add(changePictureButton, WEST);

		emptyLabel2 = new JLabel(EMPTY_LABEL_TEXT);
		add(emptyLabel2, WEST);

		addFriendField = new JTextField(TEXT_FIELD_SIZE);
		addFriendField.addActionListener(this);
		add(addFriendField, WEST);

		addFriendButton = new JButton("Add Friend");
		addFriendButton.addActionListener(this);
		add(addFriendButton, WEST);
	}

	private FacePamphletCanvas canvas;
	private FacePamphletProfile profile = null;
	private FacePamphletDatabase profileDataBase = new FacePamphletDatabase();
	private JLabel nameLabel;
	private JTextField nameField;
	private JButton addButton;
	private JButton deleteButton;
	private JButton lookUpButton;
	private JTextField changeStatusField;
	private JButton changeStatusButton;
	private JLabel emptyLabel1;
	private JTextField changePictureField;
	private JButton changePictureButton;
	private JLabel emptyLabel2;
	private JTextField addFriendField;
	private JButton addFriendButton;

}
