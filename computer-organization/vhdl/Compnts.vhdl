--2 to 1 mux
library IEEE; 
use IEEE.std_logic_1164.all;

entity mux2 is
   port(a, b: in std_logic_vector(31 downto 0);
        s: in std_logic;
        o: out std_logic_vector(31 downto 0));
end mux2;

architecture bhv of mux2 is
begin
    process(a, b, s)
    begin
        if (s = '0') then
            o <= a;
        elsif (s = '1') then
            o <= b;  
        end if;
    end process;
end bhv;

--3 bits 2 to 1 mux
library IEEE; 
use IEEE.std_logic_1164.all;

entity mux2r is
    port(a, b: in std_logic_vector(2 downto 0); 
         s: in std_logic;
         o: out std_logic_vector(2 downto 0));
end mux2r;

architecture bhv of mux2r is
begin
    process(a, b, s)
    begin
        if (s = '0') then
            o <= a;
        elsif (s = '1') then
            o <= b;  
        end if;
    end process;
end bhv;

--4 to 1 mux
library IEEE; 
use IEEE.std_logic_1164.all;

entity mux4 is
    port(c, f: in std_logic_vector(31 downto 0);
         s: in std_logic_vector(1 downto 0);
         o: out std_logic_vector(31 downto 0));
end mux4;

architecture bhv of mux4 is
begin
    process(c, f, s)
    begin
        case s is
            when "00" =>
                o <= c;
            when "01" =>
                o <= "00000000000000000000000000000001";
            when "10" =>
                o <= "00000000000000000000000000000000";
            when "11" =>
                o <= f;
            when others =>
                null;
        end case;
    end process;
end bhv;

--32 bit register
library IEEE;
use IEEE.std_logic_1164.all;

entity reg is
    port(clk, rst, enable: in std_logic;
         data: in std_logic_vector(31 downto 0); 
         o: out std_logic_vector(31 downto 0));
end reg;

architecture bhv of reg is
begin
    process(clk, enable, data)
        variable temp:std_logic_vector(31 downto 0);
    begin
        if (rst = '1') then
            temp := "00000000000000000000000000000000";
        elsif (clk = '1') then
            if enable = '1' then
                o <= data;
                temp := data;
            else
                o <= temp;
            end if;
        end if;
    end process;
end bhv;

--rising edge 32 bit register
library IEEE;
use IEEE.std_logic_1164.all;

entity regbuf is
    port(clk, enable: in std_logic; 
         data: in std_logic_vector(31 downto 0); 
         o: out std_logic_vector(31 downto 0));
end regbuf;

architecture bhv of regbuf is
begin
    process(clk, enable)
        variable temp:std_logic_vector(31 downto 0);
    begin
        if (clk'event and clk = '1') then
            if enable = '1' then
                o <= data;
                temp := data;
            else
                o <= temp;
            end if;
        end if;
    end process;
end bhv;

--sign extend
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;

entity sext is
    port(a: in std_logic_vector(15 downto 0);
         o: out std_logic_vector(31 downto 0));
end sext;

architecture bhv of sext is
begin
    process(a)
    begin
        if (a(15) = '1') then
            o <= "1111111111111111" & a;
        elsif (a(15) = '0') then
            o <= "0000000000000000" & a;
        end if;	
    end process;
end bhv;
