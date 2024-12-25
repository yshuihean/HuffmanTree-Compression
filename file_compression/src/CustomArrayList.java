import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class CustomArrayList<E> extends ArrayList<E> {
    public CustomArrayList() {
        super();
    }
    public CustomArrayList(int initialCapacity) {
        super(initialCapacity);
    }
    public CustomArrayList(Collection<? extends E> c) {
        super(c);
    }

    //自定义toString方法
    @Override
    public String toString() {
        return toStringWithSeparator("");
    }

    private String toStringWithSeparator(String s) {
        if(this.isEmpty()){
            return "";
        }

        StringBuilder result = new StringBuilder();
        for(int i=0; i<this.size(); i++){
            result.append(this.get(i).toString());
            if(i != this.size()-1){
                result.append(s);
            }
        }
        return result.toString();
    }
}