import org.junit.*;
import static org.junit.Assert.*;

public class ManualTest {

    @Test
    public void goodURL1() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("http://www.google.com"));
    }
    @Test
    public void goodURL2() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("ftp://go.com:65535/$23"));
    }
    @Test
    public void goodURL3() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("h3t://go.au:0/test1/file"));
    }
    @Test
    public void goodURL4() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("HTTP://www.google.com"));
    }
    @Test
    public void goodURL5() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("file://"));
    }
    @Test
    public void badURL1() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://."));
    }
    @Test
    public void badURL2() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://go.a1a"));
    }
    @Test
    public void badURL3() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://1.2.3.4/../"));
    }
    @Test
    public void badURL4() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://www.google.com:65a/t123"));
    }
    @Test
    public void badURL5() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://www.google.com:80/#"));
    }
}