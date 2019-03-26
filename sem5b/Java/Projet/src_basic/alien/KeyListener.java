package alien;

import javafx.scene.paint.Color;

public class KeyListener{

	private Frame mFrame;

	public KeyListener(JFrame frame) {
		mFrame = frame;
	}

	@Override
	public JFrame getParentFrame() {
		return mFrame;
	}

	@Override
	public void keyPressed(char arg0) {

	}

	@Override
	public void keyReleased(char arg0) {

	}

	@Override
	public void keyTyped(char arg0) {
		switch (arg0) {
		case '+':
			System.out.println("Add 4 neutral planet");
			Item.createPlanetBlack();
            JOptionPane.showMessageDialog(mFrame,
                    "Add 4 neutral planet ! ",
                    " Add neutral Planet",
                    JOptionPane.INFORMATION_MESSAGE);
			break;
		case '-':
			System.out.println("- has been typed");
			break;
		case 'a':
				System.out.println("App will play him self");
            JOptionPane.showMessageDialog(mFrame,
                    "App play him self",
                    "Game Notification",
                    JOptionPane.INFORMATION_MESSAGE);
            Color player1 = Color.green;
            Color player2 = Color.BLUE;


            Thread threadPlayer2 ;
            Thread threadPlayer1;

            threadPlayer1 = new Thread("Player 1") {
                public void run() {

                    while (Item.EndOfGame().equals(Color.RED)) {
                        System.out.println("run by: " + getName());
                        Item.IAPlayer(player1);
                    }

                }

            };
            threadPlayer2 = new Thread("Player 2") {
                public void run() {
                    while (Item.EndOfGame().equals(Color.RED)) {
                        System.out.println("run by: " + getName());
                        Item.IAPlayer(player2);
                    }

                }

            };



            threadPlayer1.start();
            threadPlayer2.start();
            if(!Item.EndOfGame().equals(Color.RED))
            {
                JOptionPane.showMessageDialog(mFrame,
                        "Player "+Item.toStringColor(Item.EndOfGame())+" Win the Game ! ",
                        " End of Game ",
                        JOptionPane.INFORMATION_MESSAGE);
                System.out.println("End of the Game ! ");
                mFrame.dispatchEvent(new WindowEvent(mFrame, WindowEvent.WINDOW_CLOSING));
            }

            break;


		case 'p':

            System.out.println("At the computer to play");

            Thread threadComputer=null;
            threadComputer = new Thread("Computer") {
                public void run() {
                    while (Item.EndOfGame().equals(Color.RED)) {
                        System.out.println("run by: " + getName());
                        if(Planet.firstGame !=null)
                            Item.IAPlayer(Planet.firstGame.getPlayer());

                    }

                }

            };
            threadComputer.start();
            if(!Item.EndOfGame().equals(Color.RED))
            {
                JOptionPane.showMessageDialog(mFrame,
                        "Player "+Item.toStringColor(Item.EndOfGame())+" Win the Game ! ",
                        " End of Game ",
                        JOptionPane.INFORMATION_MESSAGE);
                System.out.println("End of the Game ! ");
                mFrame.dispatchEvent(new WindowEvent(mFrame, WindowEvent.WINDOW_CLOSING));
            }


			break;

		default:
			// do nothing
			break;
		}
	}

}