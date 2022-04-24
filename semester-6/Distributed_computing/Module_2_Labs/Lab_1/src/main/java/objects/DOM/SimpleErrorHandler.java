package objects.DOM;

import org.xml.sax.ErrorHandler;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

public class SimpleErrorHandler implements ErrorHandler {

    @Override
    public void warning(SAXParseException e) throws SAXException {
        System.out.println("Рядок " +e.getLineNumber() + ":");
        System.out.println(e.getMessage());
    }

    public void error(SAXParseException e) throws SAXException {
        System.out.println("Рядок " +e.getLineNumber() + ":");
        System.out.println(e.getMessage());
    }

    public void fatalError(SAXParseException e) throws SAXException {
        System.out.println("Рядок " +e.getLineNumber() + ":");
        System.out.println(e.getMessage());
    }

}
