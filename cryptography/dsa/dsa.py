from hashlib import sha1

p = int('623358887546634156611363033027555287348687888167431500000239171720332\
116517918421401676566897139920647011904932296006424080597814478160145627774822\
951745625947064725604732240557320636380098912931623683260724371862418434610033\
8941861715113988130251202574293338708575332978108008918240726077115306442121')

q = 903569344808636464092554330241160515973915296479

g = int('267274057895153726839189862268178855179944301944977918893746276054578\
824945796251477904907487602589072412910709300333841913889446605011128807690626\
890643201293354053860194732447653838315621293114787468391961675159227250393375\
859128919913151869466165840938664887149243081067605807358135588598809906135')

x = 20131223
y = int('469189633978212800296293536832609932553395975764180914900970727574244\
972375434763774917921630700027222592604436981925068672596869883149650391591316\
047361779103855894276722058469210066538206212517497346763173031547648844549412\
252061953809459141856339274738616725460414060029257818981648654561638125942')

k = 11341111

m = 'cryptographyisthepracticeandstudyoftechniquesforsecurecommunicationinthep\
resenceofthirdpartiesmoregenerallyitisaboutconstructingandanalyzingprotocolsth\
atovercometheinfluenceofadversariesandwhicharerelatedtovariousaspectsininforma\
tionsecuritysuchasdataconfidentialitydataintegrityauthenticationandnonrepudiat\
ionmoderncryptographyintersectsthedisciplinesofmathematicscomputerscienceandel\
ectricalengineeringapplicationsofcryptographyincludeATMcardscomputerpasswordsa\
ndelectroniccommerceModerncryptographyisheavilybasedonmathematicaltheoryandcom\
putersciencepracticecryptographicalgorithmsaredesignedaroundcomputationalhardn\
essassumptionsmakingsuchalgorithmshardtobreakinpracticebyanyadversaryItistheor\
eticallypossibletobreaksuchasystembutitisinfeasibletodosobyanyknownpracticalme\
ansTheseschemesarethereforetermedcomputationallysecuretheoreticaladvancesegimp\
rovementsinintegerfactorizationalgorithmsandfastercomputingtechnologyrequireth\
esesolutionstobecontinuallyadaptedThereexistinformationtheoreticallysecuresche\
mesthatprovablycannotbebrokenevenwithunlimitedcomputingpoweranexampleistheonet\
imepadbuttheseschemesaremoredifficulttoimplementthanthebesttheoreticallybreaka\
blebutcomputationallysecuremechanisms'

def H(m):
    return int(sha1(m).hexdigest(), 16)

def exp_mod(a, b, c):
    tmp = 1
    while b > 1:
        if b & 1:
            tmp = tmp * a % c
        a = a * a % c
        b >>= 1
    return a * tmp % c

def ex_euclid(a, b):
    if b == 0:
        return 1, 0
    s, t = ex_euclid(b, a % b)
    return t, s - a / b * t

def inverse(n):
    return ex_euclid(q, n)[1]

def __main__():
    r = exp_mod(g, k, p) % q
    s = (inverse(k) * (H(m) + x * r)) % q
    print 'Signature: (%d, %d)' % (r, s)

    w = inverse(s) % q
    u1 = H(m) * w % q
    u2 = r * w % q
    v = exp_mod(g, u1, p) * exp_mod(y, u2, p) % p % q
    print 'Verification:', v

__main__()
