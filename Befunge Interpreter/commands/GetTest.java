package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;
import ru.nsu.kolochkin.Befunge.Parser;

import java.util.Stack;

import static org.junit.Assert.*;

public class GetTest {

	@Test
	public void execute() {
		//not works
		Get g = new Get();
		Stack<Character> stack = new Stack<>();
		Parser p = new Parser();
		p.read();
		stack.push('2');
		stack.push('5');
		g.execute(stack, null, null, p.field);
		assertEquals('.', (char)stack.peek());
	}
}