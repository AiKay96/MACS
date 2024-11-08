
/*
 * File: NameSurferGraph.java
 * ---------------------------
 * This class represents the canvas on which the graph of
 * names is drawn. This class is responsible for updating
 * (redrawing) the graphs whenever the list of entries changes or the window is resized.
 */

import acm.graphics.*;
import java.awt.event.*;
import java.util.*;
import java.awt.*;

public class NameSurferGraph extends GCanvas implements NameSurferConstants, ComponentListener {

	/**
	 * Creates a new NameSurferGraph object that displays the data.
	 */
	public NameSurferGraph() {
		addComponentListener(this);
	}

	/* Method: background() */
	/** Draws grid and years on canvas for background */
	private void background() {
		int year = START_DECADE;
		for (int i = 0; i < NDECADES; i++) {
			double x = i * (getWidth() / NDECADES) + 1;
			GLine line = new GLine(x, 0, x, getHeight());
			add(line);
			GLabel label = new GLabel(year + "");
			add(label, x + 1, getHeight() - GRAPH_MARGIN_SIZE + label.getHeight());
			year += 10;
		}
		GLine marginLine1 = new GLine(0, GRAPH_MARGIN_SIZE, getWidth(), GRAPH_MARGIN_SIZE);
		add(marginLine1);
		GLine marginLine2 = new GLine(0, getHeight() - GRAPH_MARGIN_SIZE, getWidth(), getHeight() - GRAPH_MARGIN_SIZE);
		add(marginLine2);
	}

	/* Method: drawGraph(entry, color) */
	/** Draws graph with data from entry and gives it appropriate color */
	private void drawGraph(NameSurferEntry entry, Color color) {
		double y = (getHeight() - 2.0 * GRAPH_MARGIN_SIZE) / MAX_RANK;
		for (int i = 0; i < NDECADES - 1; i++) {
			double x1 = i * getWidth() / NDECADES + 1;
			double x2 = x1 + getWidth() / NDECADES;
			double y1 = entry.getRank(i) * y + GRAPH_MARGIN_SIZE;
			if (entry.getRank(i) == 0) {
				y1 = getHeight() - GRAPH_MARGIN_SIZE;
			}
			double y2 = entry.getRank(i + 1) * y + GRAPH_MARGIN_SIZE;
			if (entry.getRank(i + 1) == 0) {
				y2 = getHeight() - GRAPH_MARGIN_SIZE;
			}
			GLine line = new GLine(x1, y1, x2, y2);
			line.setColor(color);
			add(line);
		}
		for (int i = 0; i < NDECADES; i++) {
			double x1 = i * getWidth() / NDECADES + 1;
			double y1 = entry.getRank(i) * y + GRAPH_MARGIN_SIZE;

			String rank = entry.getRank(i) + "";
			if (entry.getRank(i) == 0) {
				rank = "*";
			}
			GLabel name = new GLabel(entry.getName() + " " + rank);
			name.setColor(color);
			add(name, x1, y1);
		}
	}

	/* Method: clear() */
	/**
	 * Clears the list of name surfer entries stored inside this class.
	 */
	public void clear() {
		list.clear();
		update();
	}

	/* Method: addEntry(entry) */
	/**
	 * Adds a new NameSurferEntry to the list of entries on the display. Note that
	 * this method does not actually draw the graph, but simply stores the entry;
	 * the graph is drawn by calling update.
	 */
	public void addEntry(NameSurferEntry entry) {
		if (entry != null && !list.contains(entry)) {
			list.add(entry);
			update();
		}
	}

	/* Method: update() */
	/**
	 * Updates the display image by deleting all the graphical objects from the
	 * canvas and then reassembling the display according to the list of entries.
	 * Your application must call update after calling either clear or addEntry;
	 * update is also called whenever the size of the canvas changes.
	 */
	public void update() {
		removeAll();
		background();
		for (int i = 0; i < list.size(); i++) {
			Color color = Color.BLACK;
			if (i % 4 == 1) {
				color = Color.RED;
			}
			if (i % 4 == 2) {
				color = Color.BLUE;
			}
			if (i % 4 == 3) {
				color = Color.ORANGE;
			}
			drawGraph(list.get(i), color);
		}
	}

	private ArrayList<NameSurferEntry> list = new ArrayList<NameSurferEntry>();

	/* Implementation of the ComponentListener interface */
	public void componentHidden(ComponentEvent e) {
	}

	public void componentMoved(ComponentEvent e) {
	}

	public void componentResized(ComponentEvent e) {
		update();
	}

	public void componentShown(ComponentEvent e) {
	}
}
