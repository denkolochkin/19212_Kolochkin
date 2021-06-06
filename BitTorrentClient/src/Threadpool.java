import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;

public class Threadpool {

	Queue<Runnable> queue = new ArrayDeque<>();

	List<Thread> threads = new ArrayList<>();

	class Worker implements Runnable{
		@Override
		public void run() {
			while (true) {
				if (Thread.interrupted()) {
					return;
				}
				synchronized (queue) {
					while (queue.isEmpty()) {
						try {
							queue.wait();
						} catch (InterruptedException e) {
							System.out.println("Interrupted: " + Thread.currentThread().getId());
							return;
						}
					}
					Runnable task = queue.poll();
					task.run();
				}
			}
		}
	}

	public Threadpool(int numTask) {
		for (int i = 0; i < numTask; i++) {
			Thread t = new Thread(new Worker());
			threads.add(t);
			t.start();
		}
	}

	public void addTask(Runnable task) {
		synchronized (queue) {
			queue.add(task);
			queue.notify();
		}
	}

	public void stop() { threads.forEach(Thread::interrupt); }
}
