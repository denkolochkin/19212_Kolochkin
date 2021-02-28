package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class CopierVertexTest {

	@Test
	public void execute() {
		CopierVertex c = new CopierVertex();
		Stack<Character> stack = new Stack<>();
		stack.push('>');
		c.execute(stack, null, null, null);
		assertEquals(stack.pop(), stack.pop());
	}
}