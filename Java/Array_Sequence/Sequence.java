package Thinking.pravite;

interface Secletor{
    boolean end();
    Object current();
    void next();
}

public class Sequence {
    private Object[] items;
    private int next = 0;
    public Sequence(int size ){
        items = new Object[size];
    }
    public void add(Object x){
        if (next < items.length)
            items[next ++] = x;
    }

        private class SequenceSelector implements Secletor {
            private int i = 0;

            public boolean end() {
                return i == items.length;
            }

            @Override
            public Object current() {
                return items[i];
            }

            public void next() {
                if (i < items.length)
                    i++;
            }
        }

            public Secletor secletor(){
                return new SequenceSelector();
            }


            public static void main(String[] args) {
            Sequence sequence = new Sequence(10);
            for (int i = 0; i < 10; i++) {
                sequence.add(Integer.toString(i));
            }
            Secletor secletor = sequence.secletor();
            while (!secletor.end()){
                System.out.print(secletor.current() + " ");
                secletor.next();
        }
    }
}
