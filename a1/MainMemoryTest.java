package arch.sm213.machine.student;

import org.junit.Before;
import org.junit.Test;
import machine.AbstractMainMemory;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

public class MainMemoryTest {
    MainMemory m;
    @Before
    public void SetUp(){
        m =new MainMemory(128);
    }

    //test for  isAccessAligned 's functionality
    @Test
    public void TestIsAccessAligned() {
        assertEquals(true,m.isAccessAligned(0,4));
        assertEquals(true,m.isAccessAligned(4,4));
        assertEquals(true,m.isAccessAligned(8,4));
        assertEquals(true,m.isAccessAligned(2,2));
        assertEquals(false,m.isAccessAligned(5,4));
        assertEquals(false,m.isAccessAligned(1,4));
    }

    //test for  bytesToInteger 's functionality
    @Test
    public void TestBytesToInteger(){
        assertEquals(0, m.bytesToInteger((byte)00,(byte)00,(byte)00,(byte)00));
        assertEquals(8, m.bytesToInteger((byte)00,(byte)00,(byte)00,(byte)0x08));
        assertEquals(16909060, m.bytesToInteger((byte)01,(byte)02,(byte)03,(byte)0x04));
        assertEquals(128, m.bytesToInteger((byte)00,(byte)00,(byte)00,(byte)0x80));
        assertEquals(255, m.bytesToInteger((byte)00,(byte)00,(byte)00,(byte)0xff));
        assertEquals(-1, m.bytesToInteger((byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff));
        assertEquals(Integer.MAX_VALUE, m.bytesToInteger((byte)0x7f,(byte)0xff,(byte)0xff,(byte)0xff));
        assertEquals(Integer.MIN_VALUE, m.bytesToInteger((byte)0x80,(byte)00,(byte)00,(byte)00));
        assertEquals(134217728, m.bytesToInteger((byte)0x08,(byte)00,(byte)00,(byte)00));
    }

    //test for integerToBytes's functionality
    @Test
    public void TestIntegerToBytes() {
        bytesEqual(0, 0, 0, 0, m.integerToBytes(0));
        bytesEqual(0, 0, 0, 0x08, m.integerToBytes(8));
        bytesEqual(0x01, 0x02, 0x03, 0x04, m.integerToBytes(16909060));
        bytesEqual(0, 0, 0, 0x80, m.integerToBytes(128));
        bytesEqual(0, 0, 0, 0xff, m.integerToBytes(255));
        bytesEqual(0xff, 0xff, 0xff, 0xff, m.integerToBytes(-1));
        bytesEqual(0x7f, 0xff, 0xff, 0xff, m.integerToBytes(Integer.MAX_VALUE));
        bytesEqual(0x80, 0, 0, 0, m.integerToBytes(Integer.MIN_VALUE));
        bytesEqual(0x08, 0, 0, 0, m.integerToBytes(134217728));
    }

    // test for get and set's functionality
    @Test
    public void TestGetAndSet() {
        byte[] b1 = new byte[]{(byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00};
        byte[] b2 = new byte[]{(byte) 0x01, (byte) 0x02, (byte) 0x03, (byte) 0x04};
        byte[] b5 = new byte[]{(byte) 0xff, (byte) 0xff, (byte) 0xff, (byte) 0xff};
        byte[] b6 = new byte[]{(byte) 0x80, (byte) 0x00, (byte) 0x00, (byte) 0x00};
        byte[] b3 = new byte[]{1, 2, 3, 4, 5, 6, 7, 8};
        byte[] b4 = new byte[]{1};

        try {
            m.set(0, b1);
            assertArrayEquals(b1, m.get(0, b1.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("catch unexpected exception");
        }


        try {
            m.set(10, b2);
            assertArrayEquals(b2, m.get(10, b2.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("catch unexpected exception");
        }


        try {
            m.set(20, b3);
            assertArrayEquals(b3, m.get(20, b3.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("catch unexpected exception");
        }

        try {
            m.set(30, b4);
            assertArrayEquals(b4, m.get(30, b4.length));
        } catch (AbstractMainMemory.InvalidAddressException e) {
            fail("catch unexpected exception");
        }

        try {
            m.set(-1, b5);
            fail("doesn's catch the expected exception");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("catch expected exception");
        }

        try {
            m.set(128, b6);
            fail("doesn't catch the expected exception");
        } catch (AbstractMainMemory.InvalidAddressException e) {
            System.out.println("catch expected exception");
        }



    }
    private void bytesEqual(int a, int b, int c, int d, byte[] bytes) {
        assertEquals((byte)a,bytes[0]);
        assertEquals((byte)b,bytes[1]);
        assertEquals((byte)c,bytes[2]);
        assertEquals((byte)d,bytes[3]);
    }



}
