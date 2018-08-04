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
        assertTrue(urlVal.isValid("http://foo.com/blah_blah_(wikipedia)"));
    }
    @Test
    public void goodURL3() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertTrue(urlVal.isValid("ftp://happy.com"));
    }
    @Test
    public void badURL1() {
        UrlValidator urlVal = new UrlValidator(null, null,
                UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS);
        assertFalse(urlVal.isValid("http://."));
    }
}


