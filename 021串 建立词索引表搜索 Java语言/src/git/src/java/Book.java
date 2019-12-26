package git.src.java;

class Book {
    private String id;
    private String name;

    Book(String id, String name) {
        this.id = id;
        this.name = name;
    }

    @Override
    public String toString() {
        return this.name;
    }
}
