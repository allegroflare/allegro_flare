

#include <AllegroFlare/Story/Characters/PersonalityProfileMatrixFactory.hpp>




namespace AllegroFlare
{
namespace Story
{
namespace Characters
{


PersonalityProfileMatrixFactory::PersonalityProfileMatrixFactory()
{
}


PersonalityProfileMatrixFactory::~PersonalityProfileMatrixFactory()
{
}


AllegroFlare::Story::Characters::PersonalityProfileMatrix PersonalityProfileMatrixFactory::build_standard_matrix()
{
   AllegroFlare::Story::Characters::PersonalityProfileMatrix result;

   result.set_dimensions({
      { "Introversion vs. Extroversion",
        "Characters can vary in their preference for solitude or social interaction.",
        "is very introverted",
        "is introverted",
        "can show signs of introversion or extraversion depending on the situation",
        "is extroverted",
        "is very extroverted"
      },
      { "Agreeableness",
        "This trait refers to how cooperative, empathetic, and friendly a character is.",
        "is very disagreeable",
        "is disagreeable",
        "is neither agreeable or disagreeable",
        "is agreeable and cooperative",
        "is overly agreeable and a people pleaser"
      },
      { "Conscientiousness",
        "Characters with high conscientiousness are typically organized, responsible, and disciplined.",
        "is very inadvertent, very low in conscientiousness, and has difficulty with responsibility",
        "is inadvertent and disorganized",
        "is somewhat conscientious and responsible but sometimes forgetful",
        "is conscientious, well organized, and responsible",
        "is very high in conscientiousness, exceptionally organized and responsible"
      },
      { "Emotional Stability vs. Neuroticism",
        "This dimension represents how characters handle stress, uncertainty, and their overall emotional resilience.",
        "is very neurotic and has emotional collapses in stressful situations",
        "has difficulty in stressful situations",
        "handles uncertainty with a small degree of concern",
        "handles stress and uncertainty and is emotionally stable",
        "thrives in stressful situations, has very strong emotional resilience"
      },
      { "Openness to Experience",
        "Characters can differ in their curiosity, imagination, and willingness to embrace new ideas or experiences.",
        "does not like change and clings to tradition",
        "generally avoids new experiences and ideas and is content with what is",
        "is curious",
        "is exceptionally curious, imaginative, and open to new ideas",
        "seeks out and embraces new ideas and experiences"
      },
      { "Ambition vs. Contentment",
        "Some characters may be driven by ambition and a desire for achievement, while others may be more content with their current circumstances.",
        "is very content in their life",
        "content with life",
        "is generally content with life but may at times get a spark of ambition",
        "is ambitious",
        "has a very high drive for achievement"
      },
      { "Optimism vs. Pessimism",
        "Characters may have different outlooks on life, ranging from positive and hopeful to negative and cynical.",
        "is very pessimistic",
        "is somewhat pessimistic",
        "is neither pessimistic or optimistic",
        "is optimistic",
        "has a very optimistic personality"
      },
      { "Dominance vs. Submissiveness",
        "This trait reflects a character's assertiveness and desire for control versus their willingness to follow others.",
        "is very submissive, does not want to control others, and appreciates being told what to do",
        "follows others' lead",
        "can take control of situations or be submissive if the situation arises",
        "is assertive when needs to be",
        "is very assertive and craves to take control of the situation"
      },
      { "Adventurousness",
        "Characters can vary in their desire for exploration, risk-taking, and seeking out new challenges.",
        "avoids risks, exploring, and challenges",
        "avoids challenges",
        "is willing to welcome an adventure if called to do so",
        "is adventurous",
        "seeks out new challenges that involve high risk"
      },
      { "Empathy",
        "The level of empathy a character possesses influences their ability to understand and connect with others' emotions.",
        "cannot connect with others and is very socially awkward",
        "has difficulty connecting with others",
        "does not have difficulty connecting with others",
        "is insightful to others' emotions",
        "has a high degree of empathy and easily understands others' emotions even when they may not"
      },
      { "Humor",
        "Characters can have different senses of humor, ranging from witty and sarcastic to light-hearted and silly.",
        "has no sense of humor, and jokes fly over their head",
        "does not generally like to joke around",
        "has a dry sense of humor",
        "has a good sense of humor",
        "is a jokester and likes to laugh, even if it is at others' expense"
      },
      { "Trustworthiness",
        "Characters may differ in their reliability, honesty, and trustworthiness towards others.",
        "cannot be trusted in any situation and is likely being dishonest just for the sake of their own enjoyment",
        "is not very trustworthy",
        "might get a thing or two wrong and may need to be cross-checked just to be sure they are right",
        "is trustworthy",
        "is overly trustworthy and goes out of their way to be sure people can trust what they say"
      },
      { "Loyalty",
        "This trait relates to characters' commitment and faithfulness to their friends, family, or a cause.",
        "will actively rebel against friends, family, or a cause",
        "is not loyal or committed to friends, family, or a cause",
        "is mostly loyal to friends and family, but will rebel if things don't seem right",
        "is very loyal to friends and family",
        "has unwavering commitment and loyalty to friends, family, and a cause"
      },
      { "Independence vs. Dependence",
        "Some characters may be self-reliant and autonomous, while others may rely more heavily on others for support.",
        "is not very self-reliant and needs others for support",
        "relies on a moderate amount of dependence from others",
        "has some degree of independence, but does not mind relying on others",
        "is independent and self-reliant",
        "is overly self-reliant and actively goes out of their way to not be dependent on others"
      },
      { "Confidence vs. Insecurity",
        "Characters can vary in their self-assurance, self-belief, and level of confidence.",
        "is very insecure and very low in confidence",
        "is generally insecure",
        "is somewhat confident",
        "is high in confidence",
        "is overconfident and overly sure of themselves and their ideas"
      }
   });

   return result;
}


} // namespace Characters
} // namespace Story
} // namespace AllegroFlare


