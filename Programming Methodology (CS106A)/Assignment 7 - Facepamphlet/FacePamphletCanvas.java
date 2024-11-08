
/*
 * File: FacePamphletCanvas.java
 * -----------------------------
 * This class represents the canvas on which the profiles in the social
 * network are displayed.  NOTE: This class does NOT need to update the
 * display when the window is resized.
 */

import acm.graphics.*;
import java.awt.*;
import java.util.*;

public class FacePamphletCanvas extends GCanvas implements FacePamphletConstants {

	/**
	 * Constructor This method takes care of any initialization needed for the
	 * display
	 */
	public FacePamphletCanvas() {

	}

	/**
	 * This method displays a message string near the bottom of the canvas. Every
	 * time this method is called, the previously displayed message (if any) is
	 * replaced by the new message text passed in.
	 */
	public void showMessage(String msg) {
		if (message != null) {
			remove(message);
		}
		message = new GLabel(msg);
		message.setFont(MESSAGE_FONT);
		add(message, getWidth() / 2 - message.getWidth() / 2, getHeight() - BOTTOM_MESSAGE_MARGIN);
	}

	/**
	 * This method displays the given profile on the canvas. The canvas is first
	 * cleared of all existing items (including messages displayed near the bottom
	 * of the screen) and then the given profile is displayed. The profile display
	 * includes the name of the user from the profile, the corresponding image (or
	 * an indication that an image does not exist), the status of the user, and a
	 * list of the user's friends in the social network.
	 */
	public void displayProfile(FacePamphletProfile profile) {
		removeAll();
		if (message != null) {
			showMessage(message.getLabel());
		}
		if (profile != null) {
			drawName(profile.getName());
			if (profile.getImage() == null) {
				drawEmptyImage();
			} else {
				drawImage(profile.getImage());
			}
			if (profile.getStatus() == "") {
				drawStatus("No Current Status");
			} else {
				drawStatus(profile.getName() + " is " + profile.getStatus());
			}
			drawFriends(profile.getFriends());
		}

	}

	/** method to add friends list on canvas */
	private void drawFriends(Iterator<String> friends) {
		friendsLabel = new GLabel("Friends:");
		friendsLabel.setFont(PROFILE_FRIEND_LABEL_FONT);
		double x = getWidth() / 2;
		double y = LEFT_MARGIN + nameLabel.getHeight() + IMAGE_MARGIN;
		add(friendsLabel, x, y);
		double listY = y + friendsLabel.getHeight();
		while (friends.hasNext()) {
			GLabel listLabel = new GLabel(friends.next());
			listLabel.setFont(PROFILE_FRIEND_FONT);
			add(listLabel, x, listY);
			listY += listLabel.getHeight();
		}

	}

	/** method to add status on canvas */
	private void drawStatus(String status) {
		statusLabel = new GLabel(status);
		statusLabel.setFont(PROFILE_STATUS_FONT);
		add(statusLabel, LEFT_MARGIN, LEFT_MARGIN + nameLabel.getHeight() + IMAGE_MARGIN + IMAGE_WIDTH + STATUS_MARGIN
				+ statusLabel.getHeight());
	}

	/** method to add image on canvas */
	private void drawImage(GImage image) {
		picture = image;
		picture.scale(IMAGE_WIDTH / picture.getWidth(), IMAGE_HEIGHT / picture.getHeight());
		add(picture, LEFT_MARGIN, LEFT_MARGIN + nameLabel.getHeight() + IMAGE_MARGIN);
	}

	/** method to add empty image on canvas */
	private void drawEmptyImage() {
		double y = LEFT_MARGIN + nameLabel.getHeight() + IMAGE_MARGIN;
		frame = new GRect(IMAGE_WIDTH, IMAGE_HEIGHT);
		add(frame, LEFT_MARGIN, y);

		noImageLabel = new GLabel("No Image");
		noImageLabel.setFont(PROFILE_IMAGE_FONT);
		add(noImageLabel, LEFT_MARGIN + IMAGE_WIDTH / 2 - noImageLabel.getWidth() / 2,
				y + IMAGE_WIDTH / 2 + noImageLabel.getHeight() / 2);
	}

	/** method to add name on canvas */
	private void drawName(String name) {
		nameLabel = new GLabel(name);
		nameLabel.setFont(PROFILE_NAME_FONT);
		nameLabel.setColor(Color.BLUE);
		add(nameLabel, LEFT_MARGIN, TOP_MARGIN + nameLabel.getHeight());
	}

	private GLabel friendsLabel;
	private GLabel statusLabel;
	private GLabel noStatus;
	private GImage picture;
	private GLabel noImageLabel;
	private GRect frame;
	private GLabel nameLabel;
	private GLabel message;

}
