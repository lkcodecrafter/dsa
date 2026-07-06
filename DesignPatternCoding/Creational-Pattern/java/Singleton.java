class Singleton {

    private static volatile Singleton instance;
    private String data;

    private Singleton(String str) {
        data = str;
    }

    public static Singleton getInstance(String str) {

        Singleton result = instance;

        if (result == null) {

            synchronized (Singleton.class) {
                result = instance;
                if (instance == null) {
                    instance = result = new Singleton(str);
                }
            }
        }

        return result;
    }

    public String getData() {
        return this.data;
    }

    public static void main(String[] arg) {
        System.out.println(Singleton.getInstance("lalit").getData());
    }

}