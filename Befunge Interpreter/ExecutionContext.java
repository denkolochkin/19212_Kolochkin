package ru.nsu.kolochkin.Befunge;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
/**
 * This class contains field with commands,
 * stack, position on the field, direction,
 * command with name and flag for end program.
 * Also this class implements Interpreter
 * @see Interpreter
 */
public class ExecutionContext {

	protected List<List<Character>> field = new ArrayList<>();

	protected Stack<Character> stack = new Stack<>();

	protected int x;

	protected int y;

	protected Character direction = '>';

	protected Character command = null;

	protected String commandName = null;

	protected boolean end = false;

	protected MyInputStream inputStream = new MyInputStream();

	protected MyOutputStream outputStream = new MyOutputStream(inputStream.getBuffer());

	/**
	 * This method moves pointer
	 * in the indicated direction.
	 */
	public void move() {
		if (this.direction.equals('>')) {
			this.x += 1;
			if (this.x >= 80) {
				this.x -= 80;
			}
		}
		if (this.direction.equals('<')) {
			this.x -= 1;
			if (this.x < 0) {
				this.x += 80;
			}
		}
		if (this.direction.equals('^')) {
			this.y -= 1;
			if (this.y < 0) {
				this.y += 25;
			}
		}
		if (this.direction.equals('v')) {
			this.y += 1;
			if (this.y >= 25) {
				this.y -= 25;
			}
		}
	}

	public List<List<Character>> getField() { return field; }

	public Stack<Character> getStack() { return stack; }

	public int getX() { return x; }

	public int getY() { return y; }

	public Character getDirection() { return direction; }

	public Character getCommand() { return command; }

	public String getCommandName() { return commandName; }

	public boolean getEnd() { return end; }

	public MyInputStream getInputStream() { return inputStream; }

	public MyOutputStream getOutputStream() { return outputStream; }

	public void setDirection(Character a) { direction = a; }

	public void setEnd(boolean a) { end = a; }

	public void setCommand(Character a) { command = a; }

}
