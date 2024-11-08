import javax.swing.*;
import java.awt.*;

public class JBrainTetris extends JTetris{
    DefaultBrain brain;
    JCheckBox brainMode;
    JLabel okLabel;
    JSlider adversary;
    int rotate;
    int counter;
    Brain.Move move;

    Piece[] pieces;
    /**
     * Creates a new JTetris where each tetris square
     * is drawn with the given number of pixels.
     *
     * @param pixels
     */
    JBrainTetris(int pixels) {
        super(pixels);
        brain = new DefaultBrain();
        move = new Brain.Move();
        pieces = Piece.getPieces();
        counter = 0;
    }
    @Override
    public void startGame(){
        counter = 0;
        super.startGame();
    }

    @Override
    public Piece pickNextPiece() {
        int rand = random.nextInt(SLIDER_MAX_VALUE - 1) + 1;
        if (rand >= adversary.getValue()){
            okLabel.setText("ok");
            return super.pickNextPiece();
        }
        okLabel.setText("*ok*");
        int ind = -1;
        double score = Integer.MIN_VALUE;
        for(int i = 0; i < pieces.length; i++){
            Brain.Move newMove = new Brain.Move();
            brain.bestMove(board, pieces[i], board.getHeight() - TOP_SPACE, newMove);
            if(newMove.score > score){
                score = newMove.score;
                ind = i;
            }
        }
        return pieces[ind];
    }

    private JComponent createBrainPanel(){
        JPanel brainPanel = new JPanel();
        brainPanel.setLayout(new BoxLayout(brainPanel, BoxLayout.Y_AXIS));
        brainPanel.add(new JLabel("Brain:"));
        brainMode = new JCheckBox("Brain active");
        brainPanel.add(brainMode);
        return brainPanel;
    }
    private JComponent createAdversaryPanel(){
        JPanel adversaryPanel = new JPanel();
        adversaryPanel.setLayout(new BoxLayout(adversaryPanel, BoxLayout.Y_AXIS));
        adversaryPanel.add(new JLabel("Adversary:"));
        adversary = new JSlider(0, SLIDER_MAX_VALUE, 0); // min, max, current
        adversary.setPreferredSize(new Dimension(100,15));
        adversaryPanel.add(adversary);
        okLabel = new JLabel("ok");
        adversaryPanel.add(okLabel);
        return adversaryPanel;
    }
    @Override
    public JComponent createControlPanel() {
        JPanel panel = (JPanel) super.createControlPanel();
        panel.add(createBrainPanel());
        panel.add(createAdversaryPanel());
        return panel;
    }
    @Override
    public void tick(int verb) {
        if(brainMode.isSelected() && verb == DOWN){
            if(counter < super.count){
                board.undo();
                brain.bestMove(board, currentPiece, board.getHeight() - TOP_SPACE, move);
                counter = super.count;
                rotate = 0;
            }

            if(!currentPiece.equals(move.piece) && rotate < 4) {
                super.tick(ROTATE);
                rotate++;
            }
            if(move.x < currentX)
                super.tick(LEFT);
            if(move.x > currentX)
                super.tick(RIGHT);
        }
        super.tick(verb);
    }
    public static void main(String[] args) {
        // Set GUI Look And Feel Boilerplate.
        // Do this incantation at the start of main() to tell Swing
        // to use the GUI LookAndFeel of the native platform. It's ok
        // to ignore the exception.
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) { }

        JBrainTetris tetris = new JBrainTetris(16);
        JFrame frame = JBrainTetris.createFrame(tetris);
        frame.setVisible(true);
    }

    public static final int SLIDER_MAX_VALUE = 100;
}